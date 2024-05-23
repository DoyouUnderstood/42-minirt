/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:38:13 by ltd               #+#    #+#             */
/*   Updated: 2024/05/23 14:28:29 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include "cube.h"
#include "ft_error.h"
#include "functions.h"
#include "libft.h"

#include "parser.h"

t_obj_type	get_object_type(char *identifier)
{
	if (!ft_strncmp(identifier, "pl", 2))
		return (PLANE);
	else if (!ft_strncmp(identifier, "cy", 2))
		return (CYLINDER);
	else if (!ft_strncmp(identifier, "cu", 2))
		return (CUBE);
	return (INVALID_TYPE);
}

t_object	*parse_cube(char **parts);

void	parse_object(char **parts, t_world *world)
{
	t_object	*object;
	t_obj_type	type;

	object = NULL;
	type = get_object_type(parts[0]);
	if (type == PLANE)
		object = parse_plane(parts, object);
	if (type == CYLINDER)
		object = parse_cylinder_old(parts, object);
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
	specs.color = color_from_255((t_color_255){specs.color.r, specs.color.g,
			specs.color.b});
	specs.pattern = NULL;
	total_parts = 0;
	while (parts[total_parts])
		total_parts++;
	if (total_parts > 6 && parts[5] && parts[6] && parts[7])
		specs.pattern = set_pattern(parts[5], parts[6], parts[7]);
	object = cube_create(center, edge_length, specs);
	return (object);
}
