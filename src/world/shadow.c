/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:17:18 by ltd               #+#    #+#             */
/*   Updated: 2024/05/21 18:27:52 by erabbath         ###   ########.fr       */
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
	int				count;
	t_intersection	*intersections;
}					t_shadow;

bool	check_for_shadows(t_shadow *shadow)
{
	int	i;

	i = 0;
	while (i < shadow->count)
	{
		if (shadow->intersections[i].t > 0
			&& shadow->intersections[i].t < shadow->distance)
		{
			return (true);
		}
		i++;
	}
	return (false);
}

bool	is_shadowed(t_world *world, const t_tuple point)
{
	t_shadow	shadow;
	bool		in_shadow;

	if (world->light->intensity.r == 0 && world->light->intensity.g == 0
		&& world->light->intensity.b == 0)
		return (false);
	shadow.direction = tuple_subtract(world->light->pos, point);
	shadow.distance = tuple_magnitude(&shadow.direction);
	shadow.direction = vector_normalize(shadow.direction);
	shadow.shadow_ray = ray_create(point, shadow.direction);
	shadow.count = 0;
	shadow.intersections = intersect_world(world, &shadow.shadow_ray,
			&shadow.count);
	in_shadow = check_for_shadows(&shadow);
	free(shadow.intersections);
	return (in_shadow);
}
