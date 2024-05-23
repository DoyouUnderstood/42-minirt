/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:40:35 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/23 11:33:26 by erabbath         ###   ########.fr       */
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
			&d.intensity, &d.r, &d.g, &d.b))
		return ("Ambient light: Invalid format");
	if (!parser_valid_intensity(d.intensity))
		return ("Ambient light: Invalid intensity");
	if (!parser_valid_color(d.r, d.g, d.b))
		return ("Ambient light: Invalid color");
	world->amb = malloc(sizeof(t_amb_light));
	if (!world->amb)
		return ("Ambient light: malloc error");
	world->amb->color = color_from_rgb(d.r, d.g, d.b);
	world->amb->ambient = d.intensity;
	return (NULL);
}

char	*parse_camera(t_parser *parser, t_world *world)
{
	t_parser_camera	d;

	if (!world->vsize || !world->hsize)
		return ("Camera: Camera defined before resolution");
	if (!parser_match(parser, "%f,%f,%f %f,%f,%f %f%_%$",
		&d.position.x, &d.position.y, &d.position.z,
		&d.direction.x, &d.direction.y, &d.direction.z, &d.fov))
		return ("Camera: Invalid format");
	if (d.fov < 0.0 || d.fov > 180.0)	
		return ("Camera: Invalid FOV");
	d.position = point_create(d.position.x, d.position.y, d.position.z);
	d.direction = point_create(d.direction.x, d.direction.y, d.direction.z);
	world->camera = camera_create(d.fov, d.position, d.direction,
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