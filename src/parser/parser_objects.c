/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:30:49 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 07:54:45 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"
#include "cube.h"
#include "cylinder.h"
#include "ft_parser.h"
#include "plane.h"
#include "sphere.h"
#include "world.h"

#include <stdlib.h>

char	*parse_sphere(t_parser *parser, t_world *world)
{
	t_object		sphere;
	t_sphere_data	data;
	t_material		material;
	t_color_255		color_255;
	char			*error;

	material_init_default(&material);
	if (!parser_match(parser, "%f,%f,%f %f %d,%d,%d",
		&data.center.x, &data.center.y, &data.center.z,
		&data.radius, &color_255.r, &color_255.g, &color_255.b))
		return ("Sphere: Invalid format");
	data.radius = data.radius * 0.5;
	if (!color_255_validate(color_255))
		return ("Sphere: Invalid color");
	material.color = color_from_255(color_255);
	if (parse_material(parser, &material))
		return ("Sphere: Invalid material");
	data.center = point_create(data.center.x, data.center.y,
			data.center.z);
	error = sphere_init(&sphere, &data, &material);
	if (!error)
		error = world_add_object(world, &sphere);
	return (error);
}

char	*parse_cylinder(t_parser *parser, t_world *world)
{
	t_cylinder_data	cylinder;
	t_material		material;
	t_color_255		color_255;
	double			diameter;

	material_init_default(&material);
	if (!parser_match(parser, "%f,%f,%f %f,%f,%f %f %f %d,%d,%d",
		&cylinder.center.x, &cylinder.center.y, &cylinder.center.z,
		&cylinder.axis.x, &cylinder.axis.y, &cylinder.axis.z,
		&diameter, &cylinder.height, &color_255.r, &color_255.g, &color_255.b))
		return ("Cylinder: Invalid format");
	if (diameter < 0.0)
		return ("Cylinder: Invalid diameter");
	cylinder.radius = diameter / 2.0;
	if (!color_255_validate(color_255))
		return ("Cylinder: Invalid color");
	material.color = color_from_255(color_255);
	if (parse_material(parser, &material))
		return ("Cylinder: Invalid material");
	cylinder.center = point_create(cylinder.center.x, cylinder.center.y,
			cylinder.center.z);
	cylinder.axis = point_create(cylinder.axis.x, cylinder.axis.y,
			cylinder.axis.z);
	return (world_add_object(world, cylinder_create(&cylinder, &material)));
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
	if (parse_material(parser, &material))
		return ("Cube: Invalid material");
	cube.center = point_create(cube.center.x, cube.center.y,
			cube.center.z);
	return (world_add_object(world, cube_create(&cube, &material)));
}

char	*parse_plane(t_parser *parser, t_world *world)
{
	t_plane_data	plane;
	t_material		material;
	t_color_255		color_255;

	material_init_default(&material);
	if (!parser_match(parser, "%f,%f,%f %f,%f,%f %d,%d,%d",
		&plane.center.x, &plane.center.y, &plane.center.z,
		&plane.direction.x, &plane.direction.y, &plane.direction.z,
		&color_255.r, &color_255.g, &color_255.b))
		return ("Plane: Invalid format");
	if (!color_255_validate(color_255))
		return ("Plane: Invalid color");
	material.color = color_from_255(color_255);
	if (parse_material(parser, &material))
		return ("Plane: Invalid material");
	plane.center = point_create(plane.center.x, plane.center.y,
			plane.center.z);
	plane.direction = vector_create(plane.direction.x, plane.direction.y,
			plane.direction.z);
	return (world_add_object(world, plane_create(&plane, &material)));
}