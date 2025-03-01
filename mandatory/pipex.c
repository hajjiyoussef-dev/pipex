/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 19:31:20 by yhajji            #+#    #+#             */
/*   Updated: 2025/03/01 17:35:40 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void ft_process_child(char **argv, char **ev, int *fds)
{
    int in;

    in  = open(argv[1], O_RDONLY);
    
    if (in == -1)
        ft_error("Error, can not read from this file");
    dup2(in, STDIN_FILENO);
    dup2(fds[1], STDOUT_FILENO);

    close(in);
    close(fds[0]);
    close(fds[1]);
    ft_execute_cmd(argv[2], ev);
    ft_error("Error: filed in the execute parte");
}

void ft_process_parent(char **argv, char **ev, int *fds)
{
    int  out;

    out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out == -1)
        ft_error("Error: filed to open file");
    dup2(fds[0], STDIN_FILENO);
    dup2(out, STDOUT_FILENO);

    close(out);
    close(fds[1]);
    close(fds[0]);
    ft_execute_cmd(argv[3], ev);
    ft_error("Error: filed in the execute parte ");
}


int main(int argc, char **argv, char **ev)
{
    int fds[2];

    pid_t pro_id1;
    pid_t pro_id2;
    if (argc == 5)
    {
        if(pipe(fds) == -1)
            ft_error("error in pipe");
        pro_id1 = fork();
        if (pro_id1 == -1)
            ft_error("error in fork");
        if (pro_id1 == 0)
            ft_process_child(argv, ev, fds);
        pro_id2 = fork();
        if (pro_id2 == -1)
            ft_error("error in the fork");
        if (pro_id2 == 0)
            ft_process_parent(argv, ev, fds);
        close(fds[0]);
        close(fds[1]);           
    }
    else 
    {
        ft_error("Error: Bad arguments\n\
        Ex: ./pipex <file1> <cmd1> <cmd2> <file2>");
    }
    return (0);
}
