/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_help2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 00:36:08 by yhajji            #+#    #+#             */
/*   Updated: 2025/03/14 03:07:35 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_get_cmd_path_help(char *cmd, char **paths)
{
	int		i;
	char	*part_path;
	char	*real_path;

	i = 0;
	while (paths[i])
	{
		part_path = ft_str_join(paths[i], "/");
		real_path = ft_str_join(part_path, cmd);
		free(part_path);
		if (access(real_path, X_OK) == 0)
		{
			i = 0;
			while (paths[i])
			{
				free(paths[i]);
				i++;
			}
			free(paths);
			return (real_path);
		}
		free(real_path);
		i++;
	}
	return (NULL);
}

void	ft_free(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

void	ft_free_strarr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
