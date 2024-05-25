/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:40:02 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 04:56:07 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "parser.h"
#include "get_next_line.h"
#include "ft_printf.h"
#include "libft.h"
#include "world.h"
#include "functions.h"
#include "utils.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

// parse a line from the .rt file
static char	*parse_line(char *line, t_world *world)
{
	t_parser	parser;

	parser_init(&parser, line);
	if (parser_match(&parser, "%_R "))
		return (parse_resolution(&parser, world));
	if (parser_match(&parser, "%_A "))
		return (parse_ambient(&parser, world));
	if (parser_match(&parser, "%_C "))
		return (parse_camera(&parser, world));
	if (parser_match(&parser, "%_L "))
		return (parse_light(&parser, world));
	if (parser_match(&parser, "%_sp "))
		return (parse_sphere(&parser, world));
	if (parser_match(&parser, "%_cy "))
		return (parse_cylinder(&parser, world));
	if (parser_match(&parser, "%_cu "))
		return (parse_cube(&parser, world));
	if (parser_match(&parser, "%_pl "))
		return (parse_plane(&parser, world));
	return ("Invalid object prefix");
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
