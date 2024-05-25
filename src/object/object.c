/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:53:19 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 04:36:00 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lighting.h"
#include "object.h"

#include <float.h>
#include <stdlib.h>

// fonction intersect generalise
t_intersection	*object_intersect(t_object *object, t_ray *ray, int *count)
{
	t_ray		local_ray;

	*count = 0;
	local_ray = ray_transform(object->inv_transformation, *ray);
	return (object->local_intersect(object, &local_ray, count));
}

// Fonction normal_at généralisée
t_tuple	object_normal_at(t_object *obj, t_tuple world_point)
{
	t_tuple		local_point;
	t_tuple		local_normal;
	t_tuple		world_normal;

	local_point = matrix_mult_tuple(obj->inv_transformation,
			world_point);
	local_normal = obj->local_normal_at(obj, local_point);
	world_normal = matrix_mult_tuple(obj->tinv_transformation, local_normal);
	world_normal.w = 0;
	return (vector_normalize(world_normal));
}

// Fonction pour identifier le hit parmi une collection d'intersections
t_intersection	*hit(t_intersection *intersections, int count)
{
	t_intersection	*hit;
	double			min_t;
	int				i;

	i = 0;
	hit = NULL;
	min_t = DBL_MAX;
	while (i < count)
	{
		if (intersections[i].t > 0 && intersections[i].t < min_t)
		{
			hit = &intersections[i];
			min_t = intersections[i].t;
		}
		i++;
	}
	return (hit);
}

t_color	calculate_color(t_intersection *closest_hit, t_ray *ray, t_light *light)
{
	t_lighting	lighting_params;

	if (closest_hit != NULL)
	{
		lighting_params.position = malloc(sizeof(t_tuple));
		if (lighting_params.position)
			*lighting_params.position = t_point_position(ray, closest_hit->t);
		lighting_params.normalv = malloc(sizeof(t_tuple));
		if (lighting_params.normalv)
		{
			*lighting_params.normalv = closest_hit->obj->local_normal_at(
					closest_hit->obj, *lighting_params.position);
		}
		lighting_params.eyev = malloc(sizeof(t_tuple));
		if (lighting_params.eyev)
			*lighting_params.eyev = vector_negate(ray->direction);
		lighting_params.material = closest_hit->obj->material;
		lighting_params.object = closest_hit->obj;
		lighting_params.light = light;
		lighting_params.in_shadow = false;
		return (lighting(&lighting_params));
	}
	else
		return ((t_color){0, 0, 0});
}
