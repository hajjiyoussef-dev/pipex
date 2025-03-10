/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 23:22:16 by yhajji            #+#    #+#             */
/*   Updated: 2025/03/09 11:14:29 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"



void ft_print_error(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        write(2, &str[i], 1);
        i++;
    }
    // exit(1);
}
void ft_error(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        write(2, &str[i], 1);
        i++;
    }
    exit(1);
}
