/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 19:31:20 by yhajji            #+#    #+#             */
/*   Updated: 2025/02/24 18:39:01 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"



int main()
{
    pid_t pip;

    pip = fork();

    if (pip == -1)
    {
        printf("error ");
        return (1);
    }

    if (pip == 0)
    {
        printf("Child process: PID = %d, Parent PID = %d\n", getpid(), getppid());
    }
    else
    {
         printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pip)  ; 
    }

    return (0);
}

// int main(int argc, char **argv)
// {
//     int in;
//     int out; 

//     if (argc == 5)
//     {
        
//     }
// }