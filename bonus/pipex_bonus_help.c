/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_help.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 23:16:22 by yhajji            #+#    #+#             */
/*   Updated: 2025/03/12 00:41:05 by yhajji           ###   ########.fr       */
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

char *ft_create_file()
{
    char *num;
    char *file_name;
    pid_t pid;

    pid = getpid(); 
    num = ft_itoa(pid); 
    file_name = ft_str_join("/tmp/.here_doc_", num); 
    free(num);
    return file_name;
}

void here_doc(char *argv, int argc, int out)
{
    int fds[2];
    pid_t pro_id;
    char *line;
    int file_fd;
    char *file_name;
    (void)out;

    if (argc < 6)
        ft_error("./pipex_bonus here_doc <LIMITER> <cmd> <cmd1> <...> <file>\n");
    file_name = ft_create_file();
    file_fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (file_fd == -1)
        ft_error("Error: Cannot create temporary file");
    if (pipe(fds) == -1)
        ft_error("Error: in the pipe");
    pro_id = fork();
    if (pro_id == -1)
        ft_error("Error: in the fork");;
    if (pro_id == 0)
    {
        close(fds[0]);
        write(1, "pipe heredoc> ", 14);
        fflush(stdout);
        line = get_next_line(0);
        while (line)
        {
            if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
            {
                line[ft_strlen(line) - 1] = '\0';
            }
            if(ft_strncmp(line, argv, ft_strlen(argv) + 1) == 0)
            {
                // free(line);
                break;
            }
            write(file_fd, line, ft_strlen(line));
            write(file_fd, "\n", 1);
            free(line);
            write(1, "pipe heredoc> ", 14);
            fflush(stdout);
            line = get_next_line(0);
            // close(out);
        }
        close(file_fd);  // Close the file descriptor
        close(fds[1]);
        // free(line);
        exit(0);
    }
    else
    {
        waitpid(pro_id, NULL, 0);
        close(fds[1]); 
        file_fd = open(file_name, O_RDONLY);
        if (file_fd == -1)
            ft_error("Error: Cannot open temporary file");
        dup2(file_fd, STDIN_FILENO);
        close(file_fd); 
        unlink(file_name);
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
    
    if (ft_strchr(&cmd[0], '/'))
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
