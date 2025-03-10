/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:04:47 by yhajji            #+#    #+#             */
/*   Updated: 2025/03/09 22:06:49 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		while (needle[j] != '\0'
			&& haystack[i + j] == needle[j] && (i + j) < len)
		{
			j++;
		}
		if (needle[j] == '\0')
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}

char *get_cmd_path(char *cmd, char **ev)
{
    int i;
    char **paths;
    char *part_path;
    char *real_path;
    
    if (cmd[0] == '/' || cmd[0] == '.')
    {
        if (access(cmd, X_OK) == 0)
            return (ft_strdup(cmd));
        return(NULL);
    }
    i = 0;
    while (ev[i] && ft_strnstr(ev[i], "PATH=", 5) == NULL)
        i++;
    if (!ev[i])
        return (NULL);
    paths = ft_split(ev[i] + 5, ':');
    i = 0;
    while (paths[i])
    {
        part_path = ft_strjoin(paths[i], "/");
        real_path = ft_strjoin(part_path, cmd);
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
    i = 0;
    while (paths[i])
    {
        free(paths[i]);
        i++;
    }
    free(paths);
    return (NULL);
}

void ft_execute_cmd(char *argv, char **ev)
{
    char **cmd;
    char *path; 
    int i;   

    i = 0;
    cmd = ft_split(argv, ' ');
    if (!cmd || !cmd[0])  
    {
        if (cmd)
            free(cmd);
        ft_error("Error: Invalid command!");
    }
    path = get_cmd_path(cmd[0], ev);
    if (!path)
    {
        while (cmd[i])
            free(cmd[i++]);
        free(cmd);
        ft_error("Error: cmd not found!!!\n");
    }
    if (execve(path, cmd, ev) == -1)
    {
        free(path);
        while (cmd[i])
        {
            free(cmd[i]);
            i++;
        }
        free(cmd);
        ft_error("Error: in the execute f the cmd");
    }
}
