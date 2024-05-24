/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:37:18 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/24 12:07:01 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_line_rdr
{
	int		fd;
	int		is_open;
	char	buffer[BUFFER_SIZE];
	ssize_t	current;
	ssize_t	len;
}	t_line_rdr;

int		is_end_of_buffer(t_line_rdr *rdr);
void	reset_buffer(t_line_rdr *rdr);
ssize_t	fill_buffer(t_line_rdr *rdr);
char	*get_next_line(int fd);

#endif