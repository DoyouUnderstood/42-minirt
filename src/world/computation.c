/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:17:31 by ltd               #+#    #+#             */
/*   Updated: 2024/05/26 18:29:44 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computation.h"
#include "intersection.h"
#include "world.h"
#include "tuple.h"

#include "libft.h"
#define EPSILON 0.00001


void	intersect_world(t_world *world, t_ray *ray, t_intersection_arr *intersections)
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
