/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:17:18 by ltd               #+#    #+#             */
/*   Updated: 2024/05/28 11:49:30 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"
#include "functions.h"

#include <math.h>
#include <stdlib.h>

typedef struct s_shadow
{
	t_tuple			direction;
	double			distance;
	t_ray			shadow_ray;
}					t_shadow;

static bool	check_for_shadows(t_shadow *shadow, t_intersection_arr *inter)
{
	int	i;

	i = 0;
	while (i < inter->count)
	{
		if (inter->intersections[i].t > 0
			&& inter->intersections[i].t < shadow->distance)
			return (true);
		i++;
	}
	return (false);
}

bool	is_shadowed(t_world *world, const t_tuple point)
{
	t_shadow			shadow;
	t_intersection_arr	intersections;
	bool				in_shadow;

	if (world->light.color.r == 0 && world->light.color.g == 0
		&& world->light.color.b == 0)
		return (false);
	intersection_arr_init(&intersections, 60);
	shadow.direction = tuple_subtract(world->light.pos, point);
	shadow.distance = tuple_magnitude(&shadow.direction);
	shadow.direction = vector_normalize(shadow.direction);
	shadow.shadow_ray = ray_create(point, shadow.direction);
	world_intersect(world, &shadow.shadow_ray, &intersections);
	in_shadow = check_for_shadows(&shadow, &intersections);
	intersection_arr_clean(&intersections);
	return (in_shadow);
}
