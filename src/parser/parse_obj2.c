/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:38:13 by ltd               #+#    #+#             */
/*   Updated: 2024/05/21 05:26:13 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include "../graphics/graphics.h"
#include "../include/parser.h"

t_object	*create_cube(t_tuple center, double edge_length,
				t_material_specs specs);

t_obj_type	get_object_type(char *identifier)
{
	if (!strncmp(identifier, "sp", 2))
		return (SPHERE);
	else if (!strncmp(identifier, "pl", 2))
		return (PLANE);
	else if (!strncmp(identifier, "cy", 2))
		return (CYLINDER);
	else if (!strncmp(identifier, "cu", 2))
		return (CUBE);
	return (INVALID_TYPE);
}

t_object	*parse_cube(char **parts);

t_object	*create_cylinder_cap(t_cylinder *cylinder, t_color color);

void	parse_object(char **parts, t_world *world)
{
	t_object	*object;
	t_obj_type	type;

	object = NULL;
	type = get_object_type(parts[0]);
	if (type == SPHERE)
		object = parse_sphere(parts, object);
	if (type == PLANE)
		object = parse_plane(parts, object);
	if (type == CYLINDER)
		object = parse_cylinder(parts, object);
	if (type == CUBE)
		object = parse_cube(parts);
	world_add_object(world, object);
}

t_object	*parse_cube(char **parts)
{
	t_tuple				center;
	double				edge_length;
	t_material_specs	specs;
	int					total_parts;
	t_object			*object;

	if (!parse_vec3(require_str(parts[1]), &center))
		error_exit("no good coordinate\n");
	edge_length = atof(require_str(parts[2]));
	rgb(require_str(parts[3]), &specs.color);
	if (parts[4])
		specs.reflectivity = validate_reflectivity(atof(parts[4]));
	specs.color = color_from_rgb(specs.color.r, specs.color.g,
			specs.color.b);
	specs.pattern = NULL;
	total_parts = 0;
	while (parts[total_parts])
		total_parts++;
	if (total_parts > 6 && parts[5] && parts[6] && parts[7])
		specs.pattern = set_pattern(parts[5], parts[6], parts[7]);
	object = create_cube(center, edge_length, specs);
	return (object);
}

t_object	*parse_sphere(char **parts, t_object *object)
{
	t_tuple				center;
	t_material_specs	specs;
	double				diameter;
	int					total_parts;

	specs.pattern = NULL;
	specs.reflectivity = 0;
	if (!parse_vec3(require_str(parts[1]), &center))
		error_exit("Error with parsing center\n");
	if (!ft_atod(require_str(parts[2]), &diameter))
		error_exit("Error with parsing diameter\n");
	rgb(require_str(parts[3]), &specs.color);
	if (parts[4])
		specs.reflectivity = validate_reflectivity(atof(parts[4]));
	specs.color = color_from_rgb(specs.color.r, specs.color.g,
			specs.color.b);
	total_parts = 0;
	while (parts[total_parts])
		total_parts++;
	if (total_parts >= 6 && parts[5] && parts[6] && parts[7])
		specs.pattern = set_pattern(parts[5], parts[6], parts[7]);
	object = object_create_for_sphere(center, diameter, specs);
	return (object);
}

t_light	*parse_light(char **parts)
{
	t_tuple	pos;
	t_color	color;
	t_light	*light;
	double	diffuse;

	if (!parse_vec3(parts[1], &pos))
		error_exit("error with parsing\n");
	if (!ft_atod(parts[2], &diffuse))
		error_exit("error with parsing\n");
	if (!valid_bright(diffuse))
		error_exit("error with parsing\n");
	rgb(parts[3], &color);
	color = color_from_rgb(color.r, color.g, color.b);
	light = light_create(color, pos, diffuse);
	return (light);
}
