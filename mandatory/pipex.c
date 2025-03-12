/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 19:31:20 by yhajji            #+#    #+#             */
/*   Updated: 2025/03/12 03:10:01 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void ft_process_child(char **argv, char **ev, int *fds)
{
    int in;

    in  = open(argv[1], O_RDONLY);
    if (in == -1)
        ft_print_error("Error, can not read from this file\n", fds); // close pipe
    
    if (dup2(in, STDIN_FILENO) == -1)
    {
        close(in);
        ft_print_error("Error: filed in the dup2 for stdin ", fds);
    }
    if (dup2(fds[1], STDOUT_FILENO) == -1)
    {
        close(in);
        ft_print_error("Error: filed in the dup2 for stdout ", fds);
    }
    close(in);
    close(fds[0]);
    close(fds[1]);
    ft_execute_cmd(argv[2], ev);
    ft_print_error("Error: filed in the execute parte", fds);
}

void ft_process_child2(char **argv, char **ev, int *fds)
{
    int  out;

    out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out == -1)
        ft_print_error("Error: filed to open file", fds);
    if (dup2(fds[0], STDIN_FILENO) == -1)
    {
        close(out);
        ft_print_error("Error: filed in the dup2 for stdin ", fds);
    }
    if (dup2(out, STDOUT_FILENO) == -1)
    {
        close(out);
        ft_print_error("Error: filed in the dup2 for stdout ", fds);
    }
    close(out);
    close(fds[1]);
    close(fds[0]);
    ft_execute_cmd(argv[3], ev);
    ft_print_error("Error: filed in the execute parte ", fds);
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
            ft_print_error("error in fork", fds); // close pipe
        if (pro_id1 == 0)
            ft_process_child(argv, ev, fds);
        pro_id2 = fork();
        if (pro_id2 == -1)
            ft_print_error("error in the fork", fds); // close pipe
        if (pro_id2 == 0)
            ft_process_child2(argv, ev, fds);
        close(fds[0]);
        close(fds[1]);
        waitpid(pro_id1, NULL, 0);
        waitpid(pro_id2, NULL, 0);
    }
    else 
    {
        ft_error("Error: Bad arguments\n\
        Ex: ./pipex <file1> <cmd1> <cmd2> <file2>");
    }
    return (0);
}
