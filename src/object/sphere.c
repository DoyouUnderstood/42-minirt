/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:53:22 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 11:44:50 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "sphere.h"

#include <float.h>
#include <math.h>
#include <stdlib.h>

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
	t_sphere_intersect_calc	calc;
	static t_tuple			world_origin = {0, 0, 0, 0};

	(void) obj;
	calc.sphere_to_ray = tuple_subtract(ray->origin, world_origin);
	calc.a = vector_dot(ray->direction, ray->direction);
	calc.b = 2 * vector_dot(ray->direction, calc.sphere_to_ray);
	calc.c = vector_dot(calc.sphere_to_ray, calc.sphere_to_ray) - 1.0;
	calc.discriminant = calc.b * calc.b - 4 * calc.a * calc.c;
	if (calc.discriminant < -EPSILON)
	{
		*out_count = 0;
		return (NULL);
	}
	calc.discriminant_sqrt = sqrt(calc.discriminant);
	return (create_intersections(obj,
		(-calc.b - calc.discriminant_sqrt) / (2 * calc.a),
		(-calc.b + calc.discriminant_sqrt) / (2 * calc.a),
		calc.discriminant,
		out_count));
}

static t_tuple	sphere_normal_at(t_object *obj, t_tuple local_point)
{
	t_tuple	tupl;

	(void)obj;
	tupl = tuple_subtract(local_point, point_create(0, 0, 0));
	return (tupl);
}

char	*sphere_init(t_object *object, t_sphere_data *data,
	t_material *material)
{
	if (data->radius <= 0.0)
		return ("Sphere: Invalid radius");
	object->data = malloc(sizeof(t_sphere_data));
	*((t_sphere_data *) object->data) = *data;
	object->material = *material;
	object->transformation = matrix_mult(matrix_translation(data->center.x,
		data->center.y, data->center.z), matrix_scaling(data->radius, data->radius, data->radius));
	object->inv_transformation = matrix_inverse(object->transformation);
	object->tinv_transformation = matrix_transpose(object->inv_transformation);
	object->local_intersect = sphere_intersect;
	object->local_normal_at = sphere_normal_at;
	return (NULL);
}
