/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:31:21 by yhajji            #+#    #+#             */
/*   Updated: 2025/03/11 23:55:49 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
#define PIPEX_BONUS_H


#define BUFFER_SIZE 42

// delete ???
#include <stdio.h>

#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>


void ft_error(char *str);
void ft_print_error(char *str);

void ft_execute_cmd(char *argv, char **ev, int out);
char	*get_next_line(int fd);
char	*ft_str_join(char *s1, char *s2);
char	*ft_strdup(const char *s1);
int	ft_strncmp(const char *s1, const char *s2, unsigned int n);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
void here_doc(char *argv, int argc, int out);
char	*ft_strncpy(char *dest, char const *src, unsigned int n);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_itoa(int n);

#endif