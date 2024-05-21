/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:53:22 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/21 09:25:16 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"

#include "graphics.h"
#include "../include/shape.h"
#include <float.h>
#include <math.h>
#include <stdlib.h>

static t_sphere_data	*sphere_data_create(t_tuple center, double diameter)
{
	t_sphere_data	*sphere_data;

	sphere_data = malloc(sizeof(t_sphere_data));
	if (!sphere_data)
		return (NULL);
	sphere_data->center = center;
	sphere_data->diameter = diameter;
	return (sphere_data);
}

static t_intersection	*create_intersections(t_object *obj, double t1, double t2, double discriminant,
		int *out_count)
{
	t_intersection	*intersections;

	if (discriminant == 0)
	{
		*out_count = 1;
		intersections = intersection_create(obj, t1);
	}
	else
	{
		*out_count = 2;
		intersections = intersection_create_pair(obj, t1, t2);
	}
	if (!intersections)
	{
		*out_count = 0;
		return (NULL);
	}
	return (intersections);
}

static t_intersection	*sphere_intersect(t_object *obj, t_ray *ray,
		int *out_count)
{
	t_sphere_data			*sphere;
	t_sphere_intersect_data	data;

	sphere = (t_sphere_data *) obj->obj;
	data.sphere_to_ray = tuple_subtract(ray->origin, sphere->center);
	data.a = vector_dot(ray->direction, ray->direction);
	data.b = 2 * vector_dot(ray->direction, data.sphere_to_ray);
	data.c = vector_dot(data.sphere_to_ray, data.sphere_to_ray)
		- pow(sphere->diameter, 2);
	data.discriminant = data.b * data.b - 4 * data.a * data.c;
	if (data.discriminant < -EPSILON)
	{
		*out_count = 0;
		return (NULL);
	}
	data.discriminant_sqrt = sqrt(data.discriminant);
	return (create_intersections(obj,
		(-data.b - data.discriminant_sqrt) / (2 * data.a),
		(-data.b + data.discriminant_sqrt) / (2 * data.a),
		data.discriminant,
		out_count));
}

static t_tuple	sphere_normal_at(t_shape *shape, t_tuple local_point)
{
	t_tuple	tupl;

	(void)shape;
	tupl = tuple_subtract(local_point, point_create(0, 0, 0));
	return (tupl);
}

t_object	*sphere_create(t_tuple center, double diameter,
		t_material_specs specs)
{
	t_sphere_data	*sphere_data;
	t_object		*obj;

	sphere_data = sphere_data_create(center, diameter);
	obj = malloc(sizeof(t_object));
	obj->type = SPHERE;
	obj->obj = sphere_data;
	obj->shape = malloc(sizeof(t_shape));
	obj->shape->transformation = matrix_mult(matrix_translation(center.x,
				center.y, center.z), matrix_scaling(1, 1, 1));
	obj->shape->material = material_create_default(&specs.color,
			specs.reflectivity, specs.pattern);
	obj->shape->local_intersect = sphere_intersect;
	obj->shape->local_normal_at = sphere_normal_at;
	sphere_data->center = (t_tuple){0, 0, 0, 0};
	return (obj);
}
