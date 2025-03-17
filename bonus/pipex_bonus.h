/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:31:21 by yhajji            #+#    #+#             */
/*   Updated: 2025/03/16 22:59:27 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# define BUFFER_SIZE 42

# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

void	ft_error(char *str);
void	ft_print_error(char *str);

void	ft_execute_cmd(char *argv, char **ev, int out);
char	*get_next_line(int fd);
char	*ft_str_join(char *s1, char *s2);
char	*ft_strdup(const char *s1);
int		ft_strncmp(const char *s1, const char *s2, unsigned int n);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
void	here_doc(char *argv, int argc, int out);
char	*ft_strncpy(char *dest, char const *src, unsigned int n);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_itoa(int n);
char	*ft_get_cmd_path_help(char *cmd, char **path);
void	ft_free(char **paths);
void	ft_free_strarr(char **arr);
void	execute_commands(int argc, char **argv, char **ev, int *arr);
void	ft_child_process(char *argv, char **ev, int out);

#endif