/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:53:19 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 21:52:36 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lighting.h"
#include "object.h"

#include <stdlib.h>

// fonction intersect generalise
void	object_intersect(t_object *object, t_ray *ray,
	t_intersection_pair *intersections)
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

t_color	calculate_color(t_intersection *closest_hit, t_ray *ray, t_light *light)
{
	t_lighting	lighting_params;

	if (closest_hit != NULL)
	{
		lighting_params.position = t_point_position(ray, closest_hit->t);
		lighting_params.normalv = malloc(sizeof(t_tuple));
		if (lighting_params.normalv)
		{
			*lighting_params.normalv = closest_hit->obj->local_normal_at(
					closest_hit->obj, lighting_params.position);
		}
		lighting_params.eyev = malloc(sizeof(t_tuple));
		if (lighting_params.eyev)
			*lighting_params.eyev = vector_negate(ray->direction);
		lighting_params.material = &closest_hit->obj->material;
		lighting_params.object = closest_hit->obj;
		lighting_params.light = light;
		lighting_params.in_shadow = false;
		return (lighting(&lighting_params));
	}
	else
		return ((t_color){0, 0, 0});
}
