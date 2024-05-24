/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:30:49 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/24 16:39:29 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "parser.h"
#include "ft_error.h"
#include "sphere.h"
#include "cube.h"
#include "plane.h"

t_pattern	*set_pattern(char *part1, char *part2, char *part3);

char	*parse_sphere(t_parser *parser, t_world *world)
{
	t_parser_sphere	d;
	double			diameter;

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
	d.sphere.center = point_create(d.sphere.center.x, d.sphere.center.y,
			d.sphere.center.z);
	world_add_object(world, sphere_create(&d.sphere, color_from_255(d.color),
			d.reflectivity, d.pattern));
	return (NULL);
}

char	*parse_cylinder(t_parser *parser, t_world *world)
{
	t_parser_cylinder	d;
	double			diameter;

	if (!parser_match(parser, "%f,%f,%f %f,%f,%f %f %f %d,%d,%d",
		&d.cylinder.center.x, &d.cylinder.center.y, &d.cylinder.center.z,
		&d.cylinder.axis.x, &d.cylinder.axis.y, &d.cylinder.axis.z,
		&diameter, &d.cylinder.height, &d.color.r, &d.color.g, &d.color.b))
		return ("Cylinder: Invalid format");
	if (diameter < 0.0)
		return ("Cylinder: Invalid diameter");
	d.cylinder.radius = diameter / 2.0;
	if (!color_255_validate(d.color))
		return ("Cylinder: Invalid color");
	if (parse_reflectivity(parser, &d.reflectivity))
		return ("Cylinder: Invalid reflectivity");
	if (parse_pattern(parser, &d.pattern))
		return ("Cylinder: Invalid pattern");
	d.cylinder.center = point_create(d.cylinder.center.x, d.cylinder.center.y,
			d.cylinder.center.z);
	d.cylinder.axis = point_create(d.cylinder.axis.x, d.cylinder.axis.y,
			d.cylinder.axis.z);
	world_add_object(world, cylinder_create(&d.cylinder, color_from_255(d.color),
			d.reflectivity, d.pattern));
	return (NULL);
}

char	*parse_cube(t_parser *parser, t_world *world)
{
	t_cube_data	cube;
	t_material	material;
	t_color_255	color;

	material_init_default(&material);
	if (!parser_match(parser, "%f,%f,%f %f %d,%d,%d",
		&cube.center.x, &cube.center.y, &cube.center.z,
		&cube.edge_len, &color.r, &color.g, &color.b))
		return ("Cube: Invalid format");
	if (!color_255_validate(color))
		return ("Cube: Invalid color");
	material.color = color_from_255(color);
	if (parse_reflectivity(parser, &material.reflectiv))
		return ("Cube: Invalid reflectivity");
	if (parse_pattern(parser, &material.pattern))
		return ("Cube: Invalid pattern");
	cube.center = point_create(cube.center.x, cube.center.y,
			cube.center.z);
	world_add_object(world, cube_create(&cube, &material));
	return (NULL);
}

char	*parse_plane(t_parser *parser, t_world *world)
{
	t_parser_plane	d;

	if (!parser_match(parser, "%f,%f,%f %f,%f,%f %d,%d,%d",
		&d.plane.center.x, &d.plane.center.y, &d.plane.center.z,
		&d.plane.direction.x, &d.plane.direction.y, &d.plane.direction.z,
		&d.color.r, &d.color.g, &d.color.b))
		return ("Plane: Invalid format");
	if (!color_255_validate(d.color))
		return ("Plane: Invalid color");
	if (parse_reflectivity(parser, &d.reflectivity))
		return ("Plane: Invalid reflectivity");
	if (parse_pattern(parser, &d.pattern))
		return ("Plane: Invalid pattern");
	d.plane.center = point_create(d.plane.center.x, d.plane.center.y,
			d.plane.center.z);
	d.plane.direction = vector_create(d.plane.direction.x, d.plane.direction.y,
			d.plane.direction.z);
	world_add_object(world, plane_create(&d.plane, color_from_255(d.color),
			d.reflectivity, d.pattern));
	return (NULL);
}