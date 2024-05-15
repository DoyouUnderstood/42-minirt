/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltd <ltd@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:39:58 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/15 17:46:43 by ltd              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics/graphics.h"
#include "../include/parser.h"

int			parse_vec3(char *str, t_tuple *vec);
t_object	*create_cube(t_tuple center, double edge_length,
				t_material_specs specs);

t_pattern	*set_pattern(char *part1, char *part2, char *part3)
{
	t_pattern	*pattern;
	t_color		start;
	t_color		end;

	pattern = NULL;
	rgb(part2, &start);
	rgb(part3, &end);
	start = convert_color_255_to_1(start.r, start.g, start.b);
	end = convert_color_255_to_1(end.r, end.g, end.b);
	if (!strcmp(part1, "gradient"))
		pattern = gradient_pattern_create(start, end);
	else if (!strcmp(part1, "checker"))
		pattern = checker_pattern_create(start, end);
	else if (!strcmp(part1, "ring"))
		pattern = ring_pattern_create(start, end);
	else if (!ft_strncmp(part1, "stripe", 6))
		pattern = stripe_pattern_create(start, end);
	return (pattern);
}

t_object	*parse_cylinder(char **parts, t_object *obj)
{
	t_material_specs	specs;
	t_cylinder			*cyl;

	cyl = malloc(sizeof(t_cylinder));
	if (!parse_vec3(parts[1], &cyl->center))
		error_exit("error cylinder parts1\n");
	if (!parse_vec3(parts[2], &cyl->axis))
		return (NULL);
	if (!ft_atod(parts[3], &specs.diameter))
		return (NULL);
	if (!ft_atod(parts[4], &specs.height))
		return (NULL);
	rgb(parts[5], &specs.color);
	if (parts[6])
		specs.reflectivity = atof(parts[6]);
	specs.color = convert_color_255_to_1(specs.color.r, specs.color.g,
			specs.color.b);
	specs.pattern = NULL;
	if (parts[7] && parts[8] && parts[9])
		specs.pattern = set_pattern(parts[7], parts[8], parts[9]);
	obj = object_create_for_cylinder(cyl->center, cyl->axis, specs);
	free(cyl);
	return (obj);
}

// pe inverser pos et direction
t_camera	*parse_camera(char **parts, int hsize, int vsize)
{
	double		fov;
	t_camera	*camera;
	t_tuple		position;
	t_tuple		direction;

	camera = malloc(sizeof(t_camera));
	if (!parse_vec3(parts[1], &position))
		error_exit("Error with parsing position\n");
	if (!parse_vec3(parts[2], &direction))
		error_exit("Error with parsing direction\n");
	if (!ft_atod(parts[3], &fov) || !in_range(0, 70, fov))
		error_exit("Error with parsing or FOV out of range\n");
	camera->vsize = vsize;
	camera->hsize = hsize;
	camera_create(fov, position, direction, &camera);
	if (!camera)
		error_exit("Failed to create camera\n");
	return (camera);
}

int	parse_point(char *str, t_tuple *vec)
{
	int		count;
	char	*next;

	count = 0;
	vec->x = ft_strtod(str);
	next = advance_to_next_component(&str);
	if (!next)
		return (0);
	count++;
	vec->y = ft_strtod(str);
	next = advance_to_next_component(&str);
	if (!next)
		return (0);
	count++;
	vec->z = ft_strtod(str);
	count++;
	vec->w = 1;
	return (count == 3);
}

t_object	*parse_plane(char **parts, t_object *obj)
{
	t_tuple		center;
	t_color		color;
	t_tuple		direction;
	t_pattern	*pattern;
	int			total_parts;

	pattern = NULL;
	if (!parse_vec3(parts[1], &center))
		error_exit("error with parsing\n");
	else
		rgb(parts[3], &color);
	if (!parse_vec3(parts[2], &direction))
		error_exit("error with parsing\n");
	color = convert_color_255_to_1(color.r, color.g, color.b);
	total_parts = 0;
	while (parts[total_parts])
		total_parts++;
	if (total_parts >= 6 && parts[4] && parts[5] && parts[6])
		pattern = set_pattern(parts[4], parts[5], parts[6]);
	obj = object_create_for_plane(color, center, pattern, direction);
	return (obj);
}
