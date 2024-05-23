/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:40:35 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/23 14:18:50 by erabbath         ###   ########.fr       */
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
	t_parser_ambient	d;

	if (!parser_match(parser, "%f %d,%d,%d%_%$",
			&d.intensity, &d.color.r, &d.color.g, &d.color.b))
		return ("Ambient light: Invalid format");
	if (!parser_valid_intensity(d.intensity))
		return ("Ambient light: Invalid intensity");
	if (!color_255_validate(d.color))
		return ("Ambient light: Invalid color");
	world->amb = malloc(sizeof(t_amb_light));
	if (!world->amb)
		return ("Ambient light: malloc error");
	world->amb->color = color_from_255(d.color);
	world->amb->ambient = d.intensity;
	return (NULL);
}

char	*parse_camera(t_parser *parser, t_world *world)
{
	t_parser_camera	d;

	d.position = point_create(0, 0, 0);
	d.direction = point_create(0, 0, 0);
	if (!world->vsize || !world->hsize)
		return ("Camera: Camera defined before resolution");
	if (!parser_match(parser, "%f,%f,%f %f,%f,%f %f%_%$",
		&d.position.x, &d.position.y, &d.position.z,
		&d.direction.x, &d.direction.y, &d.direction.z, &d.fov))
		return ("Camera: Invalid format");
	if (d.fov < 0.0 || d.fov > 180.0)	
		return ("Camera: Invalid FOV");
	world->camera = camera_create(d.fov, d.position, d.direction,
		world->vsize, world->hsize);
	if (!world->camera)
		return ("Camera: malloc error");
	return (NULL);
}

char	*parse_light(t_parser *parser, t_world *world)
{
	t_parser_light	d;

	d.position = point_create(0, 0, 0);
	if (!parser_match(parser, "%f,%f,%f %f %d,%d,%d%_%$",
		&d.position.x, &d.position.y, &d.position.z,
		&d.intensity, &d.color.r, &d.color.g, &d.color.b))
		return ("Light: Invalid format");
	if (!parser_valid_intensity(d.intensity))
		return ("Light: Invalid intensity");
	if (!color_255_validate(d.color))
		return ("Light: Invalid color");
	world->light = light_create(color_from_255(d.color), d.position,
		d.intensity);
	if (!world->light)
		return ("Light: malloc error");
	return (NULL);
}