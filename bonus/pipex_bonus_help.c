/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_help.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 23:16:22 by yhajji            #+#    #+#             */
/*   Updated: 2025/03/09 03:14:52 by yhajji           ###   ########.fr       */
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
	return ((unsigned char )s1[i] - (unsigned char)s2[i]);
}

void here_doc(char *argv, int argc, int out)
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
        // write(1,"pipe heredoc1>", 14);
        while (1)
        {
            write(1,"pipe heredoc2>", 14);
            fflush(stdout);
            if (get_next_line(&line) <= 0)
                break;
            if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
                line[ft_strlen(line) - 1] = '\0';
            if(ft_strncmp(line, argv, ft_strlen(argv) + 1) == 0)
            {
                // free(line);
                break;
            }
            write(fds[1], line, ft_strlen(line));
            // free(line);
        }
        close(fds[1]);
        close(out);
        exit(0);
    }
    else
    {
        close(fds[1]);
        dup2(fds[0], STDIN_FILENO);
        close(fds[0]);
        waitpid(pro_id, NULL, 0);
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
    if (!paths)
        return (NULL);
    i = 0;
    while (paths[i])
    {
        part_path = ft_str_join(paths[i], "/");
        if (!part_path)
            break;

        real_path = ft_str_join(part_path, cmd);
        free(part_path);  
        if (!real_path)
            break;
        if (access(real_path, F_OK) == 0)
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
    i = -1;
    while (paths[++i])
		free(paths[i]);
	free(paths);
    return (NULL);
}



void ft_execute_cmd(char *argv, char **ev, int out)
{
    char **cmd;
    char *path; 
    int i;   

   
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
        i = 0;
        while (cmd[i])
            free(cmd[i++]);
        free(cmd);
        close(out);
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