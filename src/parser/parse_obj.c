/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:39:58 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/23 13:56:35 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"
#include "cylinder.h"
#include "cube.h"
#include "plane.h"
#include "camera.h"

#include "parser.h"

int			parse_vec3(char *str, t_tuple *vec);

t_pattern	*set_pattern(char *part1, char *part2, char *part3)
{
	t_pattern	*pattern;
	t_color		start;
	t_color		end;

	pattern = NULL;
	rgb(part2, &start);
	rgb(part3, &end);
	start = color_from_255((t_color_255){start.r, start.g, start.b});
	end = color_from_255((t_color_255){end.r, end.g, end.b});
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
	double				diameter;
	t_cylinder_data		cyl;

	if (!parse_vec3(require_str(parts[1]), &cyl.center))
		error_exit("error cylinder parts1\n");
	if (!parse_vec3(require_str(parts[2]), &cyl.axis))
		return (NULL);
	if (!ft_atod(require_str(parts[3]), &diameter))
		return (NULL);
	cyl.radius = diameter / 2.0;
	if (!ft_atod(require_str(parts[4]), &cyl.height))
		return (NULL);
	rgb(require_str(parts[5]), &specs.color);
	if (parts[6])
		specs.reflectivity = validate_reflectivity(atof(parts[6]));
	specs.color = color_from_255((t_color_255){specs.color.r, specs.color.g,
			specs.color.b});
	specs.pattern = NULL;
	if (parts[7] && parts[8] && parts[9])
		specs.pattern = set_pattern(parts[7], parts[8], parts[9]);
	obj = cylinder_create(cyl.center, cyl.radius, cyl.height, cyl.axis, specs);
	return (obj);
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
	if (!parse_vec3(require_str(parts[1]), &center))
		error_exit("error with parsing\n");
	else
		rgb(require_str(parts[3]), &color);
	if (!parse_vec3(require_str(parts[2]), &direction))
		error_exit("error with parsing\n");
	color = color_from_255((t_color_255){color.r, color.g, color.b});
	total_parts = 0;
	while (parts[total_parts])
		total_parts++;
	if (total_parts >= 6 && parts[4] && parts[5] && parts[6])
		pattern = set_pattern(parts[4], parts[5], parts[6]);
	obj = plane_create(color, center, pattern, direction);
	return (obj);
}
