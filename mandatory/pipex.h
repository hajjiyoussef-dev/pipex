/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 19:31:33 by yhajji            #+#    #+#             */
/*   Updated: 2025/03/13 22:41:25 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// delete ???
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

void	ft_print_error(char *str, int *fds);
void	ft_error(char *str);
char	**ft_split(char const *s, char c);

char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);

void	ft_execute_cmd(char *argv, char **ev);
char	*ft_get_cmd_path_help(char *cmd, char **paths);
void	ft_free(char **paths);
void	ft_free_strarr(char **arr);

#endif
