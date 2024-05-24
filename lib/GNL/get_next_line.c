/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:37:07 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/24 12:07:45 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*append_from_buffer(char *line, t_line_rdr *rdr, ssize_t len)
{
	size_t	line_len;
	char	*new_line;

	if (!line)
		line_len = 0;
	else
		line_len = ft_strlen(line);
	new_line = malloc(line_len + len + 1);
	if (!new_line)
	{
		free(line);
		return (NULL);
	}
	if (line)
		ft_strlcpy(new_line, line, line_len + 1);
	ft_strlcpy(new_line + line_len, rdr->buffer + rdr->current, len + 1);
	free(line);
	return (new_line);
}

char	*extend_line(char *line, t_line_rdr *rdr, ssize_t *found_eol)
{
	char	*new_line;
	ssize_t	eol_pos;

	eol_pos = rdr->current;
	*found_eol = 0;
	while (eol_pos < rdr->len)
	{
		if (rdr->buffer[eol_pos] == '\n')
		{
			*found_eol = 1;
			break ;
		}
		eol_pos++;
	}
	if (!*found_eol)
		new_line = append_from_buffer(line, rdr, rdr->len - rdr->current);
	else
		new_line = append_from_buffer(line, rdr, eol_pos - rdr->current + 1);
	if (new_line)
		rdr->current = eol_pos + 1;
	return (new_line);
}

char	*read_line(t_line_rdr *rdr)
{
	ssize_t	status;
	ssize_t	found_eol;
	char	*line;

	line = NULL;
	while (1)
	{
		if (is_end_of_buffer(rdr))
		{
			status = fill_buffer(rdr);
			if (status < 0)
			{
				free(line);
				return (NULL);
			}
			else if (status == 0)
				return (line);
		}
		line = extend_line(line, rdr, &found_eol);
		if (!line)
			return (NULL);
		if (found_eol)
			return (line);
	}
}

char	*get_next_line(int fd)
{
	static t_line_rdr	rdrs[10] = {0};
	size_t				i;

	i = 0;
	while (i < 10)
	{
		if (rdrs[i].fd == fd && rdrs[i].is_open)
			return (read_line(&(rdrs[i])));
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if (!rdrs[i].is_open)
		{
			rdrs[i].fd = fd;
			rdrs[i].is_open = 1;
			rdrs[i].current = 0;
			rdrs[i].len = 0;
			return (read_line(&(rdrs[i])));
		}
		i++;
	}
	return (NULL);
}
