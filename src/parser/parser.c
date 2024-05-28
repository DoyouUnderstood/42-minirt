/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:40:02 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/28 10:57:33 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"
#include "ft_parser.h"
#include "get_next_line.h"
#include "utils.h"
#include "world.h"

#include <fcntl.h>

// parse a line from the .rt file
static char	*parse_line(char *line, t_world_builder *builder)
{
	t_parser	parser;

	parser_init(&parser, line);
	if (parser_match(&parser, "%_R "))
		return (parse_resolution(&parser, builder));
	if (parser_match(&parser, "%_A "))
		return (parse_ambient(&parser, builder));
	if (parser_match(&parser, "%_C "))
		return (parse_camera(&parser, builder));
	if (parser_match(&parser, "%_L "))
		return (parse_light(&parser, builder));
	if (parser_match(&parser, "%_sp "))
		return (parse_sphere(&parser, builder));
	if (parser_match(&parser, "%_cy "))
		return (parse_cylinder(&parser, builder));
	if (parser_match(&parser, "%_co "))
		return (parse_cone(&parser, builder));
	if (parser_match(&parser, "%_cu "))
		return (parse_cube(&parser, builder));
	if (parser_match(&parser, "%_pl "))
		return (parse_plane(&parser, builder));
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
void	parse_rt_file(char *filename, t_world *world)
{
	int				fd;
	char			*line;
	char			*error;
	t_world_builder	builder;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Can't open the file");
	world_builder_init(&builder, world);
	line = get_clean_line(fd);
	while (line)
	{
		error = NULL;
		if (!is_empty_line(line))
			error = parse_line(line, &builder);
		free(line);
		if (error)
			break ;
		line = get_clean_line(fd);
	}
	close(fd);
	if (error)
		error_exit(error);
	error = world_builder_build(&builder);
}
