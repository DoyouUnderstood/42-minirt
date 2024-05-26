/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:30:49 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/26 21:16:15 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"
#include "ft_parser.h"
#include "object.h"
#include "world.h"

#include <stdlib.h>

char	*parse_sphere(t_parser *parser, t_world_builder *builder)
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
		error = world_builder_add_object(builder, &sphere);
	return (error);
}

char	*parse_cylinder(t_parser *parser, t_world_builder *builder)
{
	t_object		cylinder;
	t_cylinder_data	data;
	t_material		material;
	t_color_255		color_255;
	char			*error;

	material_init_default(&material);
	if (!parser_match(parser, "%f,%f,%f %f,%f,%f %f %f %d,%d,%d",
		&data.center.x, &data.center.y, &data.center.z,
		&data.axis.x, &data.axis.y, &data.axis.z,
		&data.radius, &data.height, &color_255.r, &color_255.g, &color_255.b))
		return ("Cylinder: Invalid format");
	data.radius = data.radius * 0.5;
	if (!color_255_validate(color_255))
		return ("Cylinder: Invalid color");
	material.color = color_from_255(color_255);
	if (parse_material(parser, &material))
		return ("Cylinder: Invalid material");
	data.center = point_create(data.center.x, data.center.y,
			data.center.z);
	data.axis = point_create(data.axis.x, data.axis.y,
			data.axis.z);
	error = cylinder_init(&cylinder, &data, &material);
	if (!error)
		error = world_builder_add_object(builder, &cylinder);
	return (error);
}

char	*parse_cube(t_parser *parser, t_world_builder *builder)
{
	t_object	cube;
	t_cube_data	data;
	t_material	material;
	t_color_255	color_255;
	char		*error;

	material_init_default(&material);
	if (!parser_match(parser, "%f,%f,%f %f %d,%d,%d",
		&data.center.x, &data.center.y, &data.center.z,
		&data.edge_len, &color_255.r, &color_255.g, &color_255.b))
		return ("Cube: Invalid format");
	if (!color_255_validate(color_255))
		return ("Cube: Invalid color");
	material.color = color_from_255(color_255);
	if (parse_material(parser, &material))
		return ("Cube: Invalid material");
	data.center = point_create(data.center.x, data.center.y,
			data.center.z);
	error = cube_init(&cube, &data, &material);
	if (!error)
		error = world_builder_add_object(builder, &cube);
	return (error);
}

char	*parse_plane(t_parser *parser, t_world_builder *builder)
{
	t_object		plane;
	t_plane_data	data;
	t_material		material;
	t_color_255		color_255;
	char			*error;

	material_init_default(&material);
	if (!parser_match(parser, "%f,%f,%f %f,%f,%f %d,%d,%d",
		&data.center.x, &data.center.y, &data.center.z,
		&data.direction.x, &data.direction.y, &data.direction.z,
		&color_255.r, &color_255.g, &color_255.b))
		return ("Plane: Invalid format");
	if (!color_255_validate(color_255))
		return ("Plane: Invalid color");
	material.color = color_from_255(color_255);
	if (parse_material(parser, &material))
		return ("Plane: Invalid material");
	data.center = point_create(data.center.x, data.center.y,
			data.center.z);
	data.direction = vector_create(data.direction.x, data.direction.y,
			data.direction.z);
	error = plane_init(&plane, &data, &material);
	if (!error)
		error = world_builder_add_object(builder, &plane);
	return (error);
}
