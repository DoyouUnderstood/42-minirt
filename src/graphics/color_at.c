/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_at.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:54:51 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 11:55:01 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computation.h"
#include "lighting.h"
#include "world.h"
#include "intersection.h"
#include "functions.h"

#include <stdlib.h>

t_color	color_at(t_world *world, t_ray *ray, int remaining)
{
	int				count;
	t_intersection	*intersections;
	t_intersection	*hit_inter;
	t_computations	comput;
	t_color			color;

	count = 0;
	intersections = intersect_world(world, ray, &count);
	if (!intersections || count == 0)
	{
		free(intersections);
		return (color_multiply_scalar(world->amb.color, world->amb.intensity));
	}
	hit_inter = intersection_hit(intersections, count);
	if (!hit_inter)
	{
		free(intersections);
		return (color_multiply_scalar(world->amb.color, world->amb.intensity));
	}
	prepare_computations(&comput, hit_inter, ray);
	color = shade_hit(world, &comput, remaining);
	free(intersections);
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
	lighting_params.position = &comps->over_point;
	lighting_params.eyev = &comps->eyev;
	lighting_params.normalv = &comps->normalv;
	lighting_params.in_shadow = is_shadowed(world, comps->over_point);
	surface = lighting(&lighting_params);
	reflected = reflected_color(world, comps, remaining);
	return (color_add(surface, reflected));
}
