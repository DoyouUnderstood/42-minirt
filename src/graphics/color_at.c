/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_at.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:54:51 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/26 19:03:44 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computation.h"
#include "lighting.h"
#include "world.h"
#include "intersection.h"
#include "functions.h"

#include <stdlib.h>

static void	prepare_computations(t_computations *comps,
		const t_intersection *intersection, const t_ray *ray)
{
	if (comps == NULL)
		return ;
	comps->t = intersection->t;
	comps->object = intersection->obj;
	comps->point = t_point_position(ray, intersection->t);
	comps->eyev = vector_negate(ray->direction);
	comps->normalv = object_normal_at(intersection->obj, comps->point);
	comps->reflectv = vector_reflect(ray->direction, comps->normalv);
	if (vector_dot(comps->normalv, comps->eyev) < 0)
	{
		comps->inside = true;
		comps->normalv = vector_negate(comps->normalv);
	}
	else
		comps->inside = false;
	comps->over_point = tuple_add(comps->point,
			tuple_scale(comps->normalv, EPSILON, EPSILON, EPSILON));
}

t_color	color_at(t_world *world, t_ray *ray, int remaining)
{
	t_intersection_arr	intersections;
	t_intersection		*hit_inter;
	t_computations		comput;
	t_color				color;

	intersection_arr_init(&intersections, 60);
	world_intersect(world, ray, &intersections);
	if (intersections.count == 0)
	{
		intersection_arr_clean(&intersections);
		return (color_multiply_scalar(world->amb.color, world->amb.intensity));
	}
	hit_inter = intersection_hit(&intersections);
	if (!hit_inter)
	{
		intersection_arr_clean(&intersections);
		return (color_multiply_scalar(world->amb.color, world->amb.intensity));
	}
	prepare_computations(&comput, hit_inter, ray);
	color = shade_hit(world, &comput, remaining);
	intersection_arr_clean(&intersections);
	return (color);
}

t_color	shade_hit(t_world *world, t_computations *comps, int remaining)
{
	t_lighting	lighting_params;
	t_color		surface;
	t_color		reflected;

	lighting_params.material = &comps->object->material;
	lighting_params.object = comps->object;
	lighting_params.light = &world->light;
	lighting_params.position = comps->over_point;
	lighting_params.eyev = comps->eyev;
	lighting_params.normalv = comps->normalv;
	lighting_params.in_shadow = is_shadowed(world, comps->over_point);
	surface = lighting(&lighting_params);
	reflected = reflected_color(world, comps, remaining);
	return (color_add(surface, reflected));
}
