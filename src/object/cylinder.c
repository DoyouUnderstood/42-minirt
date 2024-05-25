/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:53:12 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 12:01:45 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object_internal.h"
#include "material.h"
#include "utils.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

t_matrix	align_axis(t_tuple default_axis, t_tuple new_axis)
{
	t_tuple	axis;
	double	dot_product;
	double	angle;

	axis = vector_cross(default_axis, new_axis);
	dot_product = vector_dot(vector_normalize(default_axis),
			vector_normalize(new_axis));
	angle = acos(dot_product);
	return (matrix_rotation_axis(axis, angle));
}

t_intersection	*create_intersections(t_cylinder_intersect_calc *calc,
	t_object *obj, int *count)
{
	t_intersection	*intersections;
	bool			t0_intersects;
	bool			t1_intersects;

	t0_intersects = calc->y0 >= -calc->half_height && calc->y0 <= calc->half_height;
	t1_intersects = calc->y1 >= -calc->half_height && calc->y1 <= calc->half_height;
	intersections = NULL;
	if (t0_intersects && t1_intersects && !double_eq(calc->t0, calc->t1))
	{
		*count = 2;
		intersections = intersection_create_pair(obj, calc->t0, calc->t1);
	}
	else if (t0_intersects)
	{
		*count = 1;
		intersections = intersection_create(obj, calc->t0);
	}
	else if (t1_intersects)
	{
		*count = 1;
		intersections = intersection_create(obj, calc->t1);
	}
	if (!intersections)
		*count = 0;
	return (intersections);
}

t_intersection	*cylinder_intersect(t_object *obj, t_ray *ray, int *count)
{
	t_cylinder_data				*cylinder;
	t_cylinder_intersect_calc	calc;

	cylinder = (t_cylinder_data *) obj->data;
	calc.a = pow(ray->direction.x, 2) + pow(ray->direction.z, 2);
	calc.b = 2 * ray->origin.x * ray->direction.x + 2 * ray->origin.z * ray->direction.z;
	calc.c = pow(ray->origin.x, 2) + pow(ray->origin.z, 2) - pow(cylinder->radius, 2);
	calc.discriminant = pow(calc.b, 2) - 4 * calc.a * calc.c;
	if (fabs(calc.a) < EPSILON || calc.discriminant < -EPSILON)
	{
		*count = 0;
		return (NULL);
	}
	calc.discriminant_sqrt = sqrt(calc.discriminant);
	calc.t0 = (-calc.b - calc.discriminant_sqrt) / (2 * calc.a);
	calc.t1 = (-calc.b + calc.discriminant_sqrt) / (2 * calc.a);
	calc.half_height = cylinder->height / 2.0;
	calc.y0 = ray->origin.y + calc.t0 * ray->direction.y;
	calc.y1 = ray->origin.y + calc.t1 * ray->direction.y;
	return (create_intersections(&calc, obj, count));
}

t_tuple	cylinder_local_normal_at(t_object *obj, t_tuple local_point)
{
	(void) obj;
	return ((t_tuple){local_point.x, 0, local_point.z, 0});
}

char	*cylinder_init(t_object *object, t_cylinder_data *data, t_material *material)
{
	t_tuple		default_axis;
	t_matrix	rotation;

	if (data->height <= 0.0)
		return ("Cylinder: Invalid height");
	if (data->radius <= 0.0)
		return ("Cylinder: Invalid radius");
	object->data = malloc(sizeof(t_cylinder_data));
	*((t_cylinder_data *) object->data) = *data;
	object->material = *material;
	default_axis = (t_tuple){0, 1, 0, 0};
	rotation = align_axis(default_axis, data->axis);
	object->transformation = matrix_mult(matrix_translation(data->center.x,
				data->center.y, data->center.z), rotation);
	object->inv_transformation = matrix_inverse(object->transformation);
	object->tinv_transformation = matrix_transpose(object->inv_transformation);
	object->local_intersect = cylinder_intersect;
	object->local_normal_at = cylinder_local_normal_at;
	return (NULL);
}
