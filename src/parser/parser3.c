/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:30:49 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/24 16:46:27 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "parser.h"
#include "ft_error.h"
#include "sphere.h"
#include "cube.h"
#include "plane.h"

char	*parse_sphere(t_parser *parser, t_world *world)
{
	t_sphere_data	sphere;
	t_material		material;
	t_color_255		color_255;
	double			diameter;

	material_init_default(&material);
	if (!parser_match(parser, "%f,%f,%f %f %d,%d,%d",
		&sphere.center.x, &sphere.center.y, &sphere.center.z,
		&diameter, &color_255.r, &color_255.g, &color_255.b))
		return ("Sphere: Invalid format");
	if (diameter < 0.0)
		return ("Sphere: Invalid diameter");
	sphere.radius = diameter / 2.0;
	if (!color_255_validate(color_255))
		return ("Sphere: Invalid color");
	material.color = color_from_255(color_255);
	if (parse_reflectivity(parser, &material.reflectiv))
		return ("Sphere: Invalid reflectivity");
	if (parse_pattern(parser, &material.pattern))
		return ("Sphere: Invalid pattern");
	sphere.center = point_create(sphere.center.x, sphere.center.y,
			sphere.center.z);
	world_add_object(world, sphere_create(&sphere, &material));
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
	t_color_255	color_255;

	material_init_default(&material);
	if (!parser_match(parser, "%f,%f,%f %f %d,%d,%d",
		&cube.center.x, &cube.center.y, &cube.center.z,
		&cube.edge_len, &color_255.r, &color_255.g, &color_255.b))
		return ("Cube: Invalid format");
	if (!color_255_validate(color_255))
		return ("Cube: Invalid color");
	material.color = color_from_255(color_255);
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