/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:40:35 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 05:44:04 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ft_parser.h"
#include "tuple.h"
#include "world.h"

#include <stdlib.h>

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
	double		intensity;
	t_color_255	color_255;

	if (!parser_match(parser, "%f %d,%d,%d%_%$",
			&intensity, &color_255.r, &color_255.g, &color_255.b))
		return ("Ambient light: Invalid format");
	if (intensity < 0.0 || intensity > 1.0)
		return ("Ambient light: Invalid intensity");
	if (!color_255_validate(color_255))
		return ("Ambient light: Invalid color");
	world->amb = malloc(sizeof(t_amb_light));
	if (!world->amb)
		return ("Ambient light: malloc error");
	world->amb->color = color_from_255(color_255);
	world->amb->ambient = intensity;
	return (NULL);
}

char	*parse_camera(t_parser *parser, t_world *world)
{
	t_tuple	position;
	t_tuple	direction;
	double	fov;

	if (!world->vsize || !world->hsize)
		return ("Camera: Camera defined before resolution");
	if (!parser_match(parser, "%f,%f,%f %f,%f,%f %f%_%$",
		&position.x, &position.y, &position.z,
		&direction.x, &direction.y, &direction.z, &fov))
		return ("Camera: Invalid format");
	if (fov < 0.0 || fov > 180.0)	
		return ("Camera: Invalid FOV");
	position = point_create(position.x, position.y, position.z);
	direction = point_create(direction.x, direction.y, direction.z);
	world->camera = camera_create(fov, position, direction,
		world->vsize, world->hsize);
	if (!world->camera)
		return ("Camera: malloc error");
	return (NULL);
}

char	*parse_light(t_parser *parser, t_world *world)
{
	t_tuple		position;
	double		intensity;
	t_color_255	color_255;

	position = point_create(0, 0, 0);
	if (!parser_match(parser, "%f,%f,%f %f %d,%d,%d%_%$",
		&position.x, &position.y, &position.z,
		&intensity, &color_255.r, &color_255.g, &color_255.b))
		return ("Light: Invalid format");
	if (intensity < 0.0 || intensity > 1.0)
		return ("Light: Invalid intensity");
	if (!color_255_validate(color_255))
		return ("Light: Invalid color");
	world->light = light_create(color_from_255(color_255), position,
		intensity);
	if (!world->light)
		return ("Light: malloc error");
	return (NULL);
}