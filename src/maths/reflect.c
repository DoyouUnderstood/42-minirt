/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:25:32 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/22 19:07:23 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"
#include "color.h"
#include "computation.h"
#include "world.h"
#include "functions.h"

t_color	reflected_color(t_world *world, const t_computations *comps,
		int remaining)
{
	t_ray	reflect_ray;
	t_color	color;

	if (comps->object->shape->material->reflectiv == 0 || remaining <= 0)
	{
		return (color_create(0, 0, 0));
	}
	reflect_ray = ray_create(comps->over_point, comps->reflectv);
	color = color_at(world, &reflect_ray, remaining - 1);
	return (color_multiply_scalar(color,
			comps->object->shape->material->reflectiv));
}
