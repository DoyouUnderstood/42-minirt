/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:25:48 by ltd               #+#    #+#             */
/*   Updated: 2024/05/26 21:08:31 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"
#include "intersection.h"
#include "libft.h"
#include "ray.h"

#include <stdlib.h>

void	world_init(t_world *world)
{
	world->object_count = 0;
	ft_memset(&world->objects, 0, sizeof(world->objects));
}

void	world_intersect(t_world *world, t_ray *ray, t_intersection_arr *intersections)
{
	int	i;

	i = 0;
	while (i < world->object_count)
	{
		object_intersect(&world->objects[i], ray, intersections);
		i++;
	}
	intersection_arr_sort(intersections);
}
