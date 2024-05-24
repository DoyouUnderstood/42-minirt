/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:39:58 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/24 15:55:53 by erabbath         ###   ########.fr       */
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
	t_plane_data	d;
	t_color		color;
	t_pattern	*pattern;
	int			total_parts;

	pattern = NULL;
	if (!parse_vec3(require_str(parts[1]), &d.center))
		error_exit("error with parsing\n");
	else
		rgb(require_str(parts[3]), &color);
	if (!parse_vec3(require_str(parts[2]), &d.direction))
		error_exit("error with parsing\n");
	color = color_from_255((t_color_255){color.r, color.g, color.b});
	total_parts = 0;
	while (parts[total_parts])
		total_parts++;
	if (total_parts >= 6 && parts[4] && parts[5] && parts[6])
		pattern = set_pattern(parts[4], parts[5], parts[6]);
	obj = plane_create(&d, color, 0.5, pattern);
	return (obj);
}
