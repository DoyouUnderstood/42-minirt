/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:30:49 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/23 11:02:12 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "parser.h"
#include "ft_error.h"
#include "sphere.h"

t_pattern	*set_pattern(char *part1, char *part2, char *part3);

t_object	*parse_sphere_old(char **parts, t_object *object)
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
	object = sphere_create(center, diameter / 2.0, specs);
	return (object);
}

char	*parse_sphere(t_parser *parser, t_world *world)
{
	t_sphere_data		sphere_data;
	t_object			*sphere;
	double				diameter;
	t_material_specs	specs;

	if (parse_tuple(parser, &sphere_data.center, point_create))
		return ("Sphere: Invalid color");
	if (!parser_match(parser, " %f ", &diameter))
		return ("Sphere: Invalid format");
	if (diameter < 0.0)
		return ("Sphere: Invalid diameter");
	sphere_data.radius = diameter / 2.0;
	if (!parse_color(parser, &specs.color))
		return ("Sphere: Invalid color");
	if (!parser_match(parser, " %f", &specs.reflectivity))
		specs.reflectivity = 0.0;
	if (specs.reflectivity < 0.0 || specs.reflectivity > 1.0)
		return ("Sphere: Invalid reflectivity");
	parse_pattern(parser, &specs.pattern);
	if (!parser_match(parser, "%_%$"))
	{
		free(specs.pattern);
		return ("Invalid format");
	}
	sphere = sphere_create(sphere_data.center, sphere_data.radius, specs);
	if (!sphere)
	{
		free(specs.pattern);
		return ("Sphere: malloc error");
	}
	world_add_object(world, sphere);
	return (NULL);
}