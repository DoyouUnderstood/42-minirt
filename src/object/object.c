/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:53:19 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/27 17:45:49 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lighting.h"
#include "object.h"

#include <stdlib.h>

// fonction intersect generalise
void	object_intersect(t_object *object, t_ray *ray,
	t_intersection_arr *intersections)
{
	t_ray		local_ray;

	local_ray = ray_transform(object->transformations.inverse, *ray);
	object->local_intersect(object, &local_ray, intersections);
}

// Fonction normal_at généralisée
t_tuple	object_normal_at(t_object *obj, t_tuple world_point)
{
	t_tuple		local_point;
	t_tuple		local_normal;
	t_tuple		world_normal;

	local_point = matrix_mult_tuple(obj->transformations.inverse,
			world_point);
	local_normal = obj->local_normal_at(obj, local_point);
	world_normal = matrix_mult_tuple(obj->transformations.t_inverse, local_normal);
	world_normal.w = 0;
	return (vector_normalize(world_normal));
}
