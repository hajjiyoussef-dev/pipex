/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:24:16 by yhajji            #+#    #+#             */
/*   Updated: 2025/03/11 02:29:07 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int get_next_line(char **line)
{
    char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	r = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	free(buffer);
	return (r);// Return 0 if EOF with no characters read
}

// int get_next_line(char **line)
// {
//     char    *buffer;
//     int     i;
//     int     r;
//     char    c;

//     i = 0;
//     r = 0;
//     buffer = (char *)malloc(10000);
//     if (!buffer)
//         return (-1);  // Return error if malloc fails

//     // Read one character at a time until we reach a newline or EOF
//     r = read(0, &c, 1);
//     while (r > 0 && c != '\n' && c != '\0')
//     {
//         buffer[i] = c;  // Store the character in the buffer
//         i++;
//         r = read(0, &c, 1);  // Continue reading
//     }

//     // Check if we have any characters read
//     if (i == 0 && r == 0)
//     {
//         free(buffer);
//         return (0);  // Return 0 if EOF with no characters read
//     }

//     buffer[i] = '\0';  // Null-terminate the string
//     *line = buffer;  // Assign the buffer to the line pointer

//     // Don't free the buffer here, it will be freed in the caller when done with `*line`

//     return (1);  // Return 1 for successful reading
// }

