/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:31:06 by yhajji            #+#    #+#             */
/*   Updated: 2025/03/04 02:58:40 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"


int ft_open_files(char *argv, int i)
{
    int file_open;
    
    if (i == 0)
        file_open = open(argv, O_RDONLY | O_CREAT | O_APPEND, 0644);
    else if (i == 1)
        file_open = open(argv, O_RDONLY | O_CREAT | O_TRUNC, 0644);
    else if (i == 2)
        file_open = open(argv, O_RDONLY, 0644);
    else 
        return (-1);
    if (file_open == -1)
        ft_error("Error: filed to open file");
    return (file_open);
}

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
	{
		return (0);
	}
	while (s1[i] && s2[i] && (s1[i] == s2[i]) && i < (n - 1))
	{
		i++;
	}
	return ((unsigned char )s1[i] - (unsigned char)s2[i]);
}


void ft_child_process(char *argv, char **ev)
{
    pid_t pro_id;
    int fds[2];

    if (pipe(fds) == -1)
        ft_error("Error: in pipe");
    pro_id = fork();
    if (pro_id == -1)
        ft_error("Error: in fork");
    if (pro_id == 0)
    {
        close(fds[0]);
        dup2(fds[1], STDOUT_FILENO);
        close(fds[1]);
        ft_execute_cmd(argv, ev);
        ft_error("Error: filed in the execute parte");
    }
    else 
    {
        close(fds[1]);
        dup2(fds[0], STDOUT_FILENO);
        close(fds[1]);
        waitpid(pro_id, NULL, 0);
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
            in = ft_open_files(argv[argc - 1], 2);
            dup2(in, STDERR_FILENO);
            close(in);
        }
        while (i < argc - 2)
            ft_child_process(argv[i++], ev);
        dup2(out, STDOUT_FILENO);
        close(out);
        ft_execute_cmd(argv[argc - 2], ev);
        exit(1);
    }
    else 
        ft_error("Error: Bad arguments\n\
            Ex: ./pipex <file1> <cmd1> <cmd2> <file2>");
    return (0);
}
