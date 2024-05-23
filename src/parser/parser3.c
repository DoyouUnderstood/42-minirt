/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:30:49 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/23 15:05:50 by erabbath         ###   ########.fr       */
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
	double			diameter;
	t_object		*sphere;

	d.sphere.center = point_create(0, 0, 0);
	if (!parser_match(parser, "%f,%f,%f %f %d,%d,%d",
		&d.sphere.center.x, &d.sphere.center.y, &d.sphere.center.z,
		&diameter, &d.color.r, &d.color.g, &d.color.b))
		return ("Sphere: Invalid format");
	if (diameter < 0.0)
		return ("Sphere: Invalid diameter");
	d.sphere.radius = diameter / 2.0;
	if (!color_255_validate(d.color))
		return ("Sphere: Invalid color");
	if (parse_reflectivity(parser, &d.reflectivity))
		return ("Sphere: Invalid reflectivity");
	if (parse_pattern(parser, &d.pattern))
		return ("Sphere: Invalid pattern");
	sphere = sphere_create(&d.sphere, color_from_255(d.color),
		d.reflectivity, d.pattern);
	if (!sphere)
	{
		free(d.pattern);
		return ("Sphere: malloc error");
	}
	world_add_object(world, sphere);
	return (NULL);
}
