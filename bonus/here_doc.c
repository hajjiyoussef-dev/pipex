/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 00:27:39 by yhajji            #+#    #+#             */
/*   Updated: 2025/03/14 03:07:18 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_create_file(void)
{
	char	*num;
	char	*file_name;
	pid_t	pid;

	pid = getpid();
	num = ft_itoa(pid);
	file_name = ft_str_join("/tmp/.here_doc_", num);
	free(num);
	return (file_name);
}

void	here_doc(char *argv, int argc, int out)
{
	int		fds[2];
	pid_t	pro_id;
	char	*line;
	int		file_fd;
	char	*file_name;

	if (argc < 6)
		ft_error("./pipex_bonus here_doc <LIMITER> <cmd> <cmd1> <...> <file>\n");
	file_name = ft_create_file();
	file_fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file_fd == -1)
		ft_error("Error: Cannot create temporary file");
	if (pipe(fds) == -1)
		ft_error("Error: in the pipe");
	pro_id = fork();
	if (pro_id == -1)
		ft_error("Error: in the fork");
	if (pro_id == 0)
	{
		close(fds[0]);
		write(1, "pipe heredoc> ", 14);
		line = get_next_line(0);
		while (line)
		{
			if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
			{
				line[ft_strlen(line) - 1] = '\0';
			}
			if (ft_strncmp(line, argv, ft_strlen(argv) + 1) == 0)
			{
				free(line);
				break ;
			}
			write(file_fd, line, ft_strlen(line));
			free(line);
			write(1, "pipe heredoc> ", 14);
			line = get_next_line(0);
		}
		close(file_fd);
		close(fds[1]);
		free(file_name);
		close(out);
		exit(0);
	}
	else
	{
		waitpid(pro_id, NULL, 0);
		close(fds[1]);
		file_fd = open(file_name, O_RDONLY);
		if (file_fd == -1)
			ft_error("Error: Cannot open temporary file");
		dup2(file_fd, STDIN_FILENO);
		close(file_fd);
		unlink(file_name);
		free(file_name);
	}
}
