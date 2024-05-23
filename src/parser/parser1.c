/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:40:02 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/23 05:16:54 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "ft_error.h"
#include "parser.h"
#include "get_next_line.h"
#include "ft_printf.h"
#include "libft.h"
#include "world.h"
#include "functions.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

// parse a line from the .rt file
static char	*parse_line(char *line, t_world *world)
{
	t_parser	parser;
	char		**ptr;

	parser_init(&parser, line);
	parser_skip_spaces(&parser);
	ptr = ft_split(line, ' ');
	
	if (parser_match_string(&parser, "R"))
		return (parse_resolution(&parser, world));
	if (parser_match_string(&parser, "A"))
		return (parse_ambient(&parser, world));
	if (parser_match_string(&parser, "C"))
		return (parse_camera(&parser, world));
	if (parser_match_string(&parser, "L"))
		return (parse_light(&parser, world));
	else
		parse_object(ptr, world);
	free_split(ptr);
	return (NULL);
}

static bool	is_empty_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t')
			return (false);
		line++;
	}
	return (true);
}

static char	*get_clean_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (line && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	return (line);
}

// read .rt and fill and return the whole world.
t_world	*parse_rt_file(char *filename)
{
	t_world	*world;
	int		fd;
	char	*line;
	char	*error;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Can't open the file");
	world = world_create();
	line = get_clean_line(fd);
	while (line)
	{
		error = NULL;
		if (!is_empty_line(line))
			error = parse_line(line, world);
		if (error)
			break ;
		line = get_clean_line(fd);
	}
	close(fd);
	if (error)
		error_exit(error);
	error = world_validate(world);
	if (error)
		error_exit(error);
	return (world);
}
