/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:53:12 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/23 15:23:16 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include "object.h"
#include "material.h"
#include "utils.h"

#include <math.h>
#include <stdlib.h>

static t_cylinder_data	*cylinder_create_data(t_tuple center, double radius, double height,
		t_tuple axis)
{
	t_cylinder_data	*cylinder;

	cylinder = malloc(sizeof(t_cylinder_data));
	if (!cylinder)
		return (NULL);
	cylinder->center = center;
	cylinder->axis = axis;
	cylinder->radius = radius;
	cylinder->height = height;
	return (cylinder);
}

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

t_intersection	*create_intersections(t_cylinder_intersect_calc *calc, t_object *obj, int *count)
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

t_object	*cylinder_create(t_tuple center, double radius, double height, t_tuple axis,
		t_material_specs specs)
{
	t_cylinder_data	*cylinder;
	t_object	*obj;
	t_tuple		default_axis;
	t_matrix	rotation;

	cylinder = cylinder_create_data(center, radius, height, axis);
	obj = malloc(sizeof(t_object));
	obj->type = CYLINDER;
	obj->data = cylinder;
	obj->shape = malloc(sizeof(t_shape));
	default_axis = (t_tuple){0, 1, 0, 0};
	rotation = align_axis(default_axis, axis);
	obj->shape->transformation = matrix_mult(matrix_translation(center.x,
				center.y, center.z), rotation);
	obj->shape->inv_transformation = matrix_inverse(obj->shape->transformation);
	obj->shape->tinv_transformation = matrix_transpose(obj->shape->inv_transformation);
	obj->shape->material = material_create_default(&specs.color,
			specs.reflectivity, specs.pattern);
	obj->shape->local_intersect = cylinder_intersect;
	obj->shape->local_normal_at = cylinder_local_normal_at;
	return (obj);
}
