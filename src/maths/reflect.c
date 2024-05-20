/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:25:32 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/16 15:48:56 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics/graphics.h"
#include "../include/mathematique.h"
#include "../include/shape.h"
#include "../object/test_shape.h"
#include "maths.h"

t_tuple	reflect(t_tuple incident, t_tuple normal)
{
	double	scale;
	t_tuple	scaled_normal;
	t_tuple	reflection;

	scale = 2 * vector_dot(incident, normal);
	scaled_normal = tuple_scale(normal, scale, scale, scale);
	reflection = tuple_subtract(incident, scaled_normal);
	return (reflection);
}

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
