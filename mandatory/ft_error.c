/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:51:30 by yhajji            #+#    #+#             */
/*   Updated: 2025/03/14 03:05:20 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_print_error(char *str, int *fds)
{
	int	i;

	i = 0;
	close(fds[0]);
	close(fds[1]);
	while (str[i] != '\0')
	{
		write(2, &str[i], 1);
		i++;
	}
	exit(1);
}

void	ft_error(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(2, &str[i], 1);
		i++;
	}
	exit(1);
}
