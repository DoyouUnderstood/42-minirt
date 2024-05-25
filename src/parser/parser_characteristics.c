/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_characteristics.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:40:35 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 06:47:42 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ft_parser.h"
#include "tuple.h"
#include "world.h"

#include <stdlib.h>

char	*parse_resolution(t_parser *parser, t_world *world)
{
	int	width;
	int	height;

	if (!parser_match(parser, "%d %d%_%$", &width, &height))
		return ("Resolution: Invalid format");
	return (world_init_resolution(world, width, height));
}

char	*parse_camera(t_parser *parser, t_world *world)
{
	t_camera_data	camera;

	if (!world->vsize || !world->hsize)
		return ("Camera: Camera defined before resolution");
	camera.hsize = world->hsize;
	camera.vsize = world->vsize;
	if (!parser_match(parser, "%f,%f,%f %f,%f,%f %f%_%$",
		&camera.position.x, &camera.position.y, &camera.position.z,
		&camera.direction.x, &camera.direction.y, &camera.direction.z,
		&camera.fov))
		return ("Camera: Invalid format");
	camera.position = point_create(camera.position.x, camera.position.y,
			camera.position.z);
	camera.direction = point_create(camera.direction.x, camera.direction.y,
			camera.direction.z);
	return (world_init_camera(world, &camera));
}

char	*parse_ambient(t_parser *parser, t_world *world)
{
	t_amb_light	amb_light;
	t_color_255	color_255;

	if (!parser_match(parser, "%f %d,%d,%d%_%$",
			&amb_light.intensity, &color_255.r, &color_255.g, &color_255.b))
		return ("Ambient light: Invalid format");
	if (!color_255_validate(color_255))
		return ("Ambient light: Invalid color");
	amb_light.color = color_from_255(color_255);
	return (world_init_ambient(world, &amb_light));
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