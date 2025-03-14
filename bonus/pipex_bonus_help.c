/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_help.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 23:16:22 by yhajji            #+#    #+#             */
/*   Updated: 2025/03/14 03:41:32 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (i < len && haystack[i] != '\0')
	{
		j = 0;
		while (needle[j] != '\0' && haystack[i + j] == needle[j] && (i
				+ j) < len)
		{
			j++;
		}
		if (needle[j] == '\0')
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **ev, char **cmds)
{
	int		i;
	char	**paths;
	char	*result;

	if (ft_strchr(cmd, '/') && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	i = 0;
	while (ev[i] && ft_strnstr(ev[i], "PATH=", 5) == NULL)
		i++;
	if (!ev[i])
		return (NULL);
	paths = ft_split(ev[i] + 5, ':');
	if (!paths)
	{
		if (cmds)
			free(cmds);
		free(cmd);
		ft_error("Error: in geting the pathe");
	}
	result = ft_get_cmd_path_help(cmd, paths);
	if (!result)
		ft_free(paths);
	return (result);
}

void	ft_execute_cmd(char *argv, char **ev, int out)
{
	char	**cmd;
	char	*path;
	int		i;

	i = 0;
	cmd = ft_split(argv, ' ');
	if (!cmd || !cmd[0])
	{
		if (cmd)
			free(cmd);
		close(out);
		ft_error("Error: Invalid command!");
	}
	path = get_cmd_path(cmd[0], ev, cmd);
	if (!path)
	{
		while (cmd[i])
			free(cmd[i++]);
		(free(cmd), close(out));
		ft_error("Error: cmd not found!!!\n");
	}
	if (execve(path, cmd, ev) == -1)
	{
		(free(path), ft_free_strarr(cmd));
		ft_error("Error: in the execute f the cmd\n");
	}
}
