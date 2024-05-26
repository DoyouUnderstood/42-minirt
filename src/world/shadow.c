/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:17:18 by ltd               #+#    #+#             */
/*   Updated: 2024/05/26 18:27:07 by erabbath         ###   ########.fr       */
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

static bool	check_for_shadows(t_shadow *shadow, t_intersection_arr *intersections)
{
	int	i;

	i = 0;
	while (i < intersections->count)
	{
		if (intersections->intersections[i].t > 0
			&& intersections->intersections[i].t < shadow->distance)
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
	intersect_world(world, &shadow.shadow_ray, &intersections);
	in_shadow = check_for_shadows(&shadow, &intersections);
	intersection_arr_clean(&intersections);
	return (in_shadow);
}
