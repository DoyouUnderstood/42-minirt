/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:30:49 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/23 13:49:30 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "parser.h"
#include "ft_error.h"
#include "sphere.h"

t_pattern	*set_pattern(char *part1, char *part2, char *part3);

char	*parse_sphere(t_parser *parser, t_world *world)
{
	t_parser_sphere	d;
	t_object		*sphere;

	d.position = point_create(0, 0, 0);
	if (!parser_match(parser, "%f,%f,%f %f %d,%d,%d",
		&d.position.x, &d.position.y, &d.position.z,
		&d.diameter, &d.r, &d.g, &d.b))
		return ("Sphere: Invalid format");
	if (d.diameter < 0.0)
		return ("Sphere: Invalid diameter");
	if (!parser_valid_color(d.r, d.g, d.b))
		return ("Sphere: Invalid color");
	if (parse_reflectivity(parser, &d.reflectivity))
		return ("Sphere: Invalid reflectivity");
	if (parse_pattern(parser, &d.pattern))
		return ("Sphere: Invalid pattern");
	sphere = sphere_create(d.position, d.diameter / 2.0, color_from_rgb(d.r, d.g, d.b),
			d.reflectivity, d.pattern);
	if (!sphere)
	{
		free(d.pattern);
		return ("Sphere: malloc error");
	}
	world_add_object(world, sphere);
	return (NULL);
}
