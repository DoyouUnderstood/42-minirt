/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:40:02 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/22 12:05:27 by erabbath         ###   ########.fr       */
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

char	*file_to_str(const char *filename)
{
	int			fd;
	struct stat	st;
	char		*file_content;
	ssize_t		bytes_read;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_exit("error open\n");
	if (fstat(fd, &st) == -1)
		error_exit("error fstat\n");
	file_content = malloc(st.st_size + 1);
	bytes_read = read(fd, file_content, st.st_size);
	if (bytes_read == -1)
	{
		perror("Error reading file");
		free(file_content);
		close(fd);
		return (NULL);
	}
	file_content[bytes_read] = '\0';
	close(fd);
	return (file_content);
}

void	verify_world(t_world *world)
{
	if (!world->camera)
		fprintf(stderr, "Erreur : Aucune caméra définie dans le fichier.\n");
	if (!world->amb)
		fprintf(stderr,
			"Erreur : Aucune lumière ambiante définie dans le fichier.\n");
	if (!world->light)
		fprintf(stderr,
			"Erreur : Aucune lumière principale définie dans le fichier.\n");
	if (!world->objects)
		fprintf(stderr,
			"Erreur : Aucune forme géométrique définie dans le fichier.\n");
	if (!world->camera || !world->amb || !world->light || !world->objects)
	{
		fprintf(stderr,
			"Échec de chargement du monde : des composants sont manquants.\n");
		exit(EXIT_FAILURE);
	}
}

char	*parse_resolution(t_parser *parser, t_world *world)
{
	if (!parser_skip_spaces(parser))
		return ("Resolution: Missing space");
	if (!parser_consume_int(parser, &world->vsize))
		return ("Resolution: Invalid height");
	parser_skip_spaces(parser);
	if (!parser_consume_int(parser, &world->hsize))
		return ("Resolution: Invalid width");
	parser_skip_spaces(parser);
	if (!parser_match_char(parser, '\n') && !parser_at_end(parser))
		return ("Resolution: Invalid data");
	return (NULL);
}

// parse the whole .rt
char	*parse_line(char *line, t_world *world)
{
	t_parser	parser;
	char		**ptr;

	parser_init(&parser, line);
	parser_skip_spaces(&parser);
	ptr = ft_split(line, ' ');
	
	if (parser_match_string(&parser, "R"))
		return (parse_resolution(&parser, world));
	if (!ft_strncmp(ptr[0], "A", ft_strlen(ptr[0])))
		world->amb = parse_amb(ptr);
	if (!ft_strncmp(ptr[0], "C", ft_strlen(ptr[0])))
		world->camera = parse_camera(ptr, world->hsize, world->vsize);
	else if (!strncmp(ptr[0], "L", ft_strlen(ptr[0])))
		world->light = parse_light(ptr);
	else
		parse_object(ptr, world);
	free_split(ptr);
	return (NULL);
}

bool	is_empty_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t')
			return (false);
		line++;
	}
	return (true);
}

// read .rt and fill and return the whole world.
t_world	*read_and_parse(char *filename)
{
	t_world	*world;
	int		fd;
	char	*line;
	char	*error;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Can't open the file");
	world = world_create();
	line = get_next_line(fd);
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (!is_empty_line(line))
			error = parse_line(line, world);
		if (error)
		{
			close(fd);
			error_exit(error);
		}
		line = get_next_line(fd);
	}
	close(fd);
	verify_world(world);
	return (world);
}
