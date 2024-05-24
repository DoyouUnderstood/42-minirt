/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:37:24 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/24 12:07:36 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	is_end_of_buffer(t_line_rdr *rdr)
{
	return (rdr->current >= rdr->len);
}

void	reset_buffer(t_line_rdr *rdr)
{
	rdr->is_open = 0;
	rdr->current = 0;
	rdr->len = 0;
}

ssize_t	fill_buffer(t_line_rdr *rdr)
{
	rdr->len = read(rdr->fd, rdr->buffer, BUFFER_SIZE);
	if (rdr->len == 0)
		reset_buffer(rdr);
	else if (rdr->len > 0)
		rdr->current = 0;
	return (rdr->len);
}
