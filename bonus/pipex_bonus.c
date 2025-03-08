/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:31:06 by yhajji            #+#    #+#             */
/*   Updated: 2025/03/08 03:27:12 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"


int ft_open_files(char *argv, int i)
{
    int file_open;
    
    // fprintf(stderr, "hannnnnaaanananan\n");
    file_open = 0;
    if (i == 0)
        file_open = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
    else if (i == 1)
        file_open = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    else if (i == 2)
        file_open = open(argv, O_RDONLY, 0777);
    if (file_open == -1)
        ft_print_error("Error: filed to open file");
    return (file_open);
}




void ft_child_process(char *argv, char **ev, int out)
{
    pid_t	pid;
	int		p_fd[2];

	if (pipe(p_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (pid == 0)
	{
		close(p_fd[0]);
		dup2(p_fd[1], STDOUT_FILENO);
        close(p_fd[1]);
		ft_execute_cmd(argv, ev, out);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], STDIN_FILENO);
        close(p_fd[0]);
	}
}

int main(int argc, char **argv, char **ev)
{
    int i;
    int in;
    int out;

    if (argc >= 5)
    {
        if (ft_strncmp(argv[1], "here_doc", 8) == 0)
        {
            i = 3;
            out = ft_open_files(argv[argc - 1], 0);
            here_doc(argv[2], argc);
        }
        else 
        {
            i = 2;
            out = ft_open_files(argv[argc - 1], 1);
            in = ft_open_files(argv[1], 2);
            dup2(in, STDIN_FILENO);
            close(in);
        }
        while (i < argc - 2)
        {
            ft_child_process(argv[i], ev, out);
            i++;
        }
        dup2(out, STDOUT_FILENO);
        close(out);
        ft_execute_cmd(argv[argc - 2], ev, out);
        close(out);
        exit(1);
    }
    else 
        ft_error("Error: Bad arguments\n\
            Ex: ./pipex <file1> <cmd1> <cmd2> <file2>");
    return (0);
}
