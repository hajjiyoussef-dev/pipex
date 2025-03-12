/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:54:58 by yhajji            #+#    #+#             */
/*   Updated: 2025/03/11 23:55:35 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"


static int	num_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	else
		len = 0;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	unsigned int	num;
	char			*str;
	int				len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = num_len(n);
	str = (char *) malloc((len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
		num = (n * -1);
	else
		num = n;
	if (n < 0)
		str[0] = '-';
	while (len-- && num)
	{
		str[len] = (num % 10) + '0';
		num = num / 10;
	}
	if (n == 0)
		str[0] = '0';
	return (str);
}
