/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:31:21 by yhajji            #+#    #+#             */
/*   Updated: 2025/03/03 17:41:10 by yhajji           ###   ########.fr       */
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


void ft_error(char *str);

void ft_execute_cmd(char *argv, char **ev);
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *s1);
void	*ft_memcpy(void *dest, const void *src, size_t n);


#endif