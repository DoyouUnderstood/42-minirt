/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:40:35 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/23 07:42:49 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "ft_error.h"
#include "parser.h"
#include "tuple.h"

char	*parse_resolution(t_parser *parser, t_world *world)
{
	if (!parser_match(parser, "%d %d%_%$", &world->vsize, &world->hsize))
		return ("Resolution: Invalid format");
	if (world->vsize < 1)
		return ("Resolution: Invalid height");
	if (world->hsize < 1)
		return ("Resolution: Invalid width");
	return (NULL);
}

char	*parse_ambient(t_parser *parser, t_world *world)
{
	char		*error;

	world->amb = malloc(sizeof(t_amb_light));
	if (!world->amb)
		return ("Ambient light: malloc error");
	if (!parser_match(parser, "%f ",
		&world->amb->ambient))
		error = "Ambient light: Invalid format";
	if (!error && (world->amb->ambient < 0.0 || world->amb->ambient > 1.0))
		error = "Ambient light: Invalid intensity value";
	if (!error && parse_color(parser, &world->amb->color))
		error = "Ambient light: Invalid color";
	if (!error && !parser_match(parser, "%_%$"))
		error = "Ambient light: Invalid format";
	if (error)
	{
		free(world->amb);
		world->amb = NULL;
	}
	return (error);
}

char	*parse_camera(t_parser *parser, t_world *world)
{
	t_tuple	position;
	t_tuple	direction;
	double	fov;

	if (!world->vsize || !world->hsize)
		return ("Camera: Camera defined before resolution");
	if (parse_tuple(parser, &position, point_create))
		return ("Camera: Error parsing position");
	if (!parser_match(parser, " "))
		return ("Camera: Invalid format");
	if (parse_tuple(parser, &direction, vector_create))
		return ("Camera: Error parsing direction");
	if (!parser_match(parser, " %f%_%$", &fov))
		return ("Camera: Invalid format");
	if (fov < 0.0 || fov > 70.0)
		return ("Camera: Invalid field of view");
	world->camera = camera_create(fov, position, direction,
		world->vsize, world->hsize);
	if (!world->camera)
		return ("Camera: malloc error");
	return (NULL);
}

char	*parse_light(t_parser *parser, t_world *world)
{
	t_tuple	position;
	double	intensity;
	t_color	color;

	if (parse_tuple(parser, &position, point_create))
		return ("Light: Invalid position");
	if (!parser_match(parser, " %f ", &intensity))
		return ("Light: Invalid format");
	if (intensity < 0.0 || intensity > 1.0)
		return ("Light: Invalid intensity");
	if (parse_color(parser, &color))
		return ("Light: Invalid color");
	if (!parser_match(parser, "%_%$"))
		return ("Light: Invalid format");
	world->light = light_create(color, position, intensity);
	if (!world->light)
		return ("Light: malloc error");
	return (NULL);
}