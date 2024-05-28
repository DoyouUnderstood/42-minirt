/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_characteristics.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:40:35 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/28 10:58:38 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ft_parser.h"
#include "tuple.h"
#include "world.h"

#include <stdlib.h>

char	*parse_resolution(t_parser *parser, t_world_builder *builder)
{
	int	width;
	int	height;

	if (!parser_match(parser, "%d %d%_%$", &width, &height))
		return ("Resolution: Invalid format");
	return (world_builder_set_resolution(builder, width, height));
}

char	*parse_camera(t_parser *parser, t_world_builder *builder)
{
	t_camera_data	camera;

	if (!parser_match(parser, "%f,%f,%f %f,%f,%f %f%_%$",
			&camera.position.x, &camera.position.y, &camera.position.z,
			&camera.direction.x, &camera.direction.y, &camera.direction.z,
			&camera.fov))
		return ("Camera: Invalid format");
	camera.position = point_create(camera.position.x, camera.position.y,
			camera.position.z);
	camera.direction = point_create(camera.direction.x, camera.direction.y,
			camera.direction.z);
	return (world_builder_set_camera(builder, &camera));
}

char	*parse_ambient(t_parser *parser, t_world_builder *builder)
{
	t_amb_light	amb_light;
	t_color_255	color_255;

	if (!parser_match(parser, "%f %d,%d,%d%_%$",
			&amb_light.intensity, &color_255.r, &color_255.g, &color_255.b))
		return ("Ambient light: Invalid format");
	if (!color_255_validate(color_255))
		return ("Ambient light: Invalid color");
	amb_light.color = color_from_255(color_255);
	return (world_builder_set_ambient(builder, &amb_light));
}

char	*parse_light(t_parser *parser, t_world_builder *builder)
{
	t_light		light;
	t_color_255	color_255;

	if (!parser_match(parser, "%f,%f,%f %f %d,%d,%d%_%$",
			&light.pos.x, &light.pos.y, &light.pos.z,
			&light.intensity, &color_255.r, &color_255.g, &color_255.b))
		return ("Light: Invalid format");
	if (!color_255_validate(color_255))
		return ("Light: Invalid color");
	light.color = color_from_255(color_255);
	light.pos = point_create(light.pos.x, light.pos.y, light.pos.z);
	return (world_builder_set_light(builder, &light));
}
