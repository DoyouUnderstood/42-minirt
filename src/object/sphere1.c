/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:53:22 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/20 11:58:12 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics/graphics.h"
#include "../include/shape.h"
#include "../object/test_shape.h"
#include "test_shape.h"
#include <float.h>
#include <math.h>
#include <stdlib.h>

static t_sphere	*sphere_create(t_tuple center, double diameter)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->center = center;
	sphere->diameter = diameter;
	return (sphere);
}

t_object	*object_create_for_sphere(t_tuple center, double diameter,
		t_material_specs specs)
{
	t_sphere	*sphere;
	t_object	*obj;

	sphere = sphere_create(center, diameter);
	obj = malloc(sizeof(t_object));
	obj->type = SPHERE;
	obj->obj = sphere;
	obj->shape = malloc(sizeof(t_shape));
	obj->shape->transformation = matrix_mult(matrix_translation(center.x,
				center.y, center.z), matrix_scaling(1, 1, 1));
	obj->shape->material = material_create_default(&specs.color,
			specs.reflectivity, specs.pattern);
	obj->shape->local_intersect = local_intersect_sphere;
	obj->shape->local_normal_at = local_normal_at_sphere;
	sphere->center = (t_tuple){0, 0, 0, 0};
	return (obj);
}

t_intersection	*create_intersections(const t_interparams *params,
		int *out_count)
{
	t_intersection	*intersections;

	if (params->discriminant == 0)
	{
		*out_count = 1;
	}
	else
	{
		*out_count = 2;
	}
	intersections = malloc(sizeof(t_intersection) * (*out_count));
	if (!intersections)
	{
		*out_count = 0;
		return (NULL);
	}
	intersections[0] = intersection_create(params->t1, params->obj);
	if (*out_count == 2)
		intersections[1] = intersection_create(params->t2, params->obj);
	return (intersections);
}

void	calculate_abc(const t_ray *ray, const t_sphere *sphere,
		t_abcparams *params)
{
	t_tuple	sphere_to_ray;

	sphere_to_ray = tuple_subtract(ray->origin, sphere->center);
	params->a = vector_dot(ray->direction, ray->direction);
	params->b = 2 * vector_dot(ray->direction, sphere_to_ray);
	params->c = vector_dot(sphere_to_ray, sphere_to_ray) - pow(sphere->diameter,
			2);
}

double	calculate_discriminant(const t_abcparams *params)
{
	return (params->b * params->b - 4 * params->a * params->c);
}
