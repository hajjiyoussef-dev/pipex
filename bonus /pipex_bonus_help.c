/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_help.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 23:16:22 by yhajji            #+#    #+#             */
/*   Updated: 2025/03/03 03:15:15 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"



void here_doc(char *argv, int argc)
{
    int fds[2];
    pid_t pro_id;
    char *line;

    if (argc < 6)
        ft_error("./pipex_bonus here_doc <LIMITER> <cmd> <cmd1> <...> <file>\n");
    
    if (pipe(fds) == -1)
        ft_error("Error: in the pipe");
    pro_id = fork();
    if (pro_id == -1)
        ft_error("Error: in the fork");;
    if (pro_id == 0)
    {
        close(fds[0]);
        while (get_next_line(&line))
        {
            /* code */
        }
        
    }    
    
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
        if (access(real_path, F_OK | R_OK) == 0)
        {
              i = 0;
              while (paths[i])
              {
                free(paths[i]);
                i++;
              }
              free(paths);
              printf("%s", real_path);
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
    path = get_cmd_path(cmd[0], ev);
    if (!path)
    {
        while (cmd[i])
            free(cmd[i++]);
        free(cmd);
        ft_error("Error: cmd not found!!! ");
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