/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 19:31:33 by yhajji            #+#    #+#             */
/*   Updated: 2025/02/28 22:40:12 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

// delete ???
#include <stdio.h>

#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>

#define BUFFER_SIZE 42


void ft_error(char *str);
char	**ft_split(char const *s, char c);
char	*get_next_line(int fd);

char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
void	*ft_memcpy(void *dest, const void *src, size_t n);


void ft_execute_cmd(char *argv, char **ev);


#endif 
