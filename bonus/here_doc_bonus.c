/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 00:27:39 by yhajji            #+#    #+#             */
/*   Updated: 2025/03/16 22:58:46 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_create_file(void)
{
	char		*num;
	char		*file_name;
	static int	count;

	count = 0;
	while (1)
	{
		num = ft_itoa(count++);
		file_name = ft_str_join("/tmp/.here_doc_", num);
		free(num);
		if (access(file_name, F_OK) != 0)
			break ;
		free(file_name);
	}
	return (file_name);
}

void	write_to_tmp_file(char *file_name, char *argv, int *fds, int out)
{
	char	*line;
	int		file_fd;

	file_fd = open(file_name, O_WRONLY | O_APPEND);
	close(fds[0]);
	write(1, "pipe heredoc> ", 14);
	line = get_next_line(0);
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (!line || ft_strncmp(line, argv, ft_strlen(argv) + 1) == 0)
			break ;
		write(file_fd, line, ft_strlen(line));
		write(file_fd, "\n", 1);
		free(line);
		write(1, "pipe heredoc> ", 14);
		line = get_next_line(0);
	}
	if (line)
		free(line);
	get_next_line(-1);
	(close(file_fd), close(fds[1]));
	(free(file_name), close(out));
	exit(0);
}

void	read_from_tmp_file(char *file_name, int *fds)
{
	int	file_fd;

	waitpid(-1, NULL, 0);
	close(fds[1]);
	file_fd = open(file_name, O_RDONLY);
	if (file_fd == -1)
		ft_error("Error: Cannot open temporary file");
	dup2(file_fd, STDIN_FILENO);
	close(file_fd);
	unlink(file_name);
	free(file_name);
	close(fds[0]);
}

pid_t	setup_process(char *file_name, int *fds, int out)
{
	int		file_fd;
	pid_t	pro_id;

	file_fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file_fd == -1)
		(close(out), free(file_name),
			ft_error("Error: Cannot create temporary file\n"));
	if (pipe(fds) == -1)
		(close(file_fd), close(out), free(file_name),
			ft_error("Error: in the pipe"));
	pro_id = fork();
	if (pro_id == -1)
		(close(file_fd), close(out), free(file_name), close(fds[0]),
			close(fds[1]), ft_error("Error: in the fork"));
	close(file_fd);
	return (pro_id);
}

void	here_doc(char *argv, int argc, int out)
{
	int		fds[2];
	pid_t	pro_id;
	char	*file_name;

	if (argc < 6)
	{
		close(out);
		ft_error("./pipex_bonus here_doc <LIMITER> <cmd> <cmd1> <...> <file>\n");
	}
	file_name = ft_create_file();
	pro_id = setup_process(file_name, fds, out);
	if (pro_id == 0)
		write_to_tmp_file(file_name, argv, fds, out);
	else
		read_from_tmp_file(file_name, fds);
}
