/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:40:35 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/22 18:01:19 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "ft_error.h"
#include "parser.h"
#include "tuple.h"

char	*parse_resolution(t_parser *parser, t_world *world)
{
	if (!parser_skip_spaces(parser))
		return ("Resolution: Missing space");
	if (!parser_consume_int(parser, &world->vsize) || world->vsize < 1)
		return ("Resolution: Invalid height");
	parser_skip_spaces(parser);
	if (!parser_consume_int(parser, &world->hsize) || world->hsize < 1)
		return ("Resolution: Invalid width");
	parser_skip_spaces(parser);
	if (!parser_match_char(parser, '\n') && !parser_at_end(parser))
		return ("Resolution: Invalid data at end of line");
	return (NULL);
}

char	*parse_ambient(t_parser *parser, t_world *world)
{
	t_amb_light	*amb_light;
	char		*error;

	amb_light = malloc(sizeof(t_amb_light));
	if (!amb_light)
		return ("Ambient light: malloc error");
	if (!parser_skip_spaces(parser))
		return (parser_handle_error(amb_light, "Ambient light: Missing space after A"));
	if (!parser_consume_double(parser, &amb_light->ambient))
		return (parser_handle_error(amb_light, "Ambient light: Invalid intensity"));
	if (!parser_skip_spaces(parser))
		return (parser_handle_error(amb_light, "Ambient light: Missing space after intensity"));
	error = parse_color(parser, &amb_light->color);
	if (error)
		return (parser_handle_error(amb_light, error));
	parser_skip_spaces(parser);
	if (!parser_match_char(parser, '\n') && !parser_at_end(parser))
		return ("Ambient light: Invalid data at end of line");
	world->amb = amb_light;
	return (NULL);
}

char	*parse_camera(t_parser *parser, t_world *world)
{
	t_tuple	position;
	t_tuple	direction;
	double	fov;

	if (!world->vsize || !world->hsize)
		return ("Camera: Camera defined before resolution");
	if (!parser_skip_spaces(parser))
		return ("Camera: Missing space after C");
	if (parse_tuple(parser, &position, point_create))
		return ("Camera: Error parsing position");
	if (!parser_skip_spaces(parser))
		return ("Camera: Missing space after position");
	if (parse_tuple(parser, &direction, vector_create))
		return ("Camera: Error parsing direction");
	if (!parser_skip_spaces(parser))
		return ("Camera: Missing space after direction");
	if (!parser_consume_double(parser, &fov) || fov < 0.0 || fov > 70.0)
		return ("Camera: Invalid field of view");
	parser_skip_spaces(parser);
	if (!parser_match_char(parser, '\n') && !parser_at_end(parser))
		return ("Camera: Invalid data at end of line");
	world->camera = camera_create(fov, position, direction,
		world->vsize, world->hsize);
	if (!world->camera)
		return ("Camera: malloc error");
	return (NULL);
}

char	*parse_light(t_parser *parser, t_world *world)
{
	t_tuple	position;
	double	diffuse;
	t_color	color;

	if (!parser_skip_spaces(parser))
		return ("Light: Missing space after L");
	if (parse_tuple(parser, &position, point_create))
		return ("Light: Invalid position");
	if (!parser_skip_spaces(parser))
		return ("Light: Missing space after position");
	if (!parser_consume_double(parser, &diffuse) || diffuse < 0.0 || diffuse > 1.0)
		return ("Light: Invalid diffuse parameter");
	if (!parser_skip_spaces(parser))
		return ("Light: Missing space after diffuse parameter");
	if (parse_color(parser, &color))
		return ("Light: Invalid color");
	parser_skip_spaces(parser);
	if (!parser_match_char(parser, '\n') && !parser_at_end(parser))
		return ("Light: Invalid data at end of line");
	world->light = light_create(color, position, diffuse);
	if (!world->light)
		return ("Light: malloc error");
	return (NULL);
}