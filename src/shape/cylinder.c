/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:53:12 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/21 18:30:44 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include "object.h"
#include "material.h"
#include "utils.h"

#include <math.h>
#include <stdlib.h>

static t_cylinder_data	*cylinder_create_data(t_tuple center, double diameter, double height,
		t_tuple axis)
{
	t_cylinder_data	*cylinder;

	cylinder = malloc(sizeof(t_cylinder_data));
	if (!cylinder)
		return (NULL);
	cylinder->center = center;
	cylinder->axis = axis;
	cylinder->radius = diameter / 2.0;
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

t_intersection	*create_intersections(t_cylinder_intersect_data *data, t_object *obj, int *count)
{
	t_intersection	*intersections;
	bool			t0_intersects;
	bool			t1_intersects;

	t0_intersects = data->y0 >= -data->half_height && data->y0 <= data->half_height;
	t1_intersects = data->y1 >= -data->half_height && data->y1 <= data->half_height;
	intersections = NULL;
	if (t0_intersects && t1_intersects && !double_eq(data->t0, data->t1))
	{
		*count = 2;
		intersections = intersection_create_pair(obj, data->t0, data->t1);
	}
	else if (t0_intersects)
	{
		*count = 1;
		intersections = intersection_create(obj, data->t0);
	}
	else if (t1_intersects)
	{
		*count = 1;
		intersections = intersection_create(obj, data->t1);
	}
	if (!intersections)
		*count = 0;
	return (intersections);
}

t_intersection	*cylinder_intersect(t_object *obj, t_ray *ray, int *count)
{
	t_cylinder_data				*cylinder;
	t_cylinder_intersect_data	data;

	cylinder = (t_cylinder_data *) obj->obj;
	data.a = pow(ray->direction.x, 2) + pow(ray->direction.z, 2);
	data.b = 2 * ray->origin.x * ray->direction.x + 2 * ray->origin.z * ray->direction.z;
	data.c = pow(ray->origin.x, 2) + pow(ray->origin.z, 2) - pow(cylinder->radius, 2);
	data.discriminant = pow(data.b, 2) - 4 * data.a * data.c;
	if (fabs(data.a) < EPSILON || data.discriminant < -EPSILON)
	{
		*count = 0;
		return (NULL);
	}
	data.discriminant_sqrt = sqrt(data.discriminant);
	data.t0 = (-data.b - data.discriminant_sqrt) / (2 * data.a);
	data.t1 = (-data.b + data.discriminant_sqrt) / (2 * data.a);
	data.half_height = cylinder->height / 2.0;
	data.y0 = ray->origin.y + data.t0 * ray->direction.y;
	data.y1 = ray->origin.y + data.t1 * ray->direction.y;
	return (create_intersections(&data, obj, count));
}

t_tuple	cylinder_local_normal_at(t_shape *shape, t_tuple local_point)
{
	(void)shape;
	return ((t_tuple){local_point.x, 0, local_point.z, 0});
}

t_object	*cylinder_create(t_tuple center, t_tuple axis,
		t_material_specs specs)
{
	t_cylinder_data	*cylinder;
	t_object	*obj;
	t_tuple		default_axis;
	t_matrix	rotation;

	cylinder = cylinder_create_data(center, specs.diameter, specs.height, axis);
	obj = malloc(sizeof(t_object));
	obj->type = CYLINDER;
	obj->obj = cylinder;
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
