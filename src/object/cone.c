/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:53:12 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/27 15:55:49 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object_internal.h"
#include "material.h"
#include "utils.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

static t_matrix	align_axis(t_tuple default_axis, t_tuple new_axis)
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

static void	cone_intersect(t_object *obj, t_ray *ray,
	t_intersection_arr *intersections)
{
	t_cylinder_intersect_calc	calc;

	(void) obj;
	calc.a = pow(ray->direction.x, 2) - pow(ray->direction.y, 2)
		+ pow(ray->direction.z, 2);
	calc.b = 2 * ray->origin.x * ray->direction.x
		- 2 * ray->origin.y * ray->direction.y
		+ 2 * ray->origin.z * ray->direction.z;
	calc.c = pow(ray->origin.x, 2) - pow(ray->origin.y, 2)
		+ pow(ray->origin.z, 2);
	if (double_eq(calc.a, 0.0))
	{
		if (double_eq(calc.b, 0.0))
			return ;
		intersection_arr_add(intersections, obj, -calc.c / (2 * calc.b));
		return ;
	}
	calc.discriminant = pow(calc.b, 2) - 4 * calc.a * calc.c;
	if (fabs(calc.a) < EPSILON || calc.discriminant < -EPSILON)
		return ;
	calc.discriminant_sqrt = sqrt(calc.discriminant);
	calc.t0 = (-calc.b - calc.discriminant_sqrt) / (2 * calc.a);
	calc.t1 = (-calc.b + calc.discriminant_sqrt) / (2 * calc.a);
	intersection_arr_add(intersections, obj, calc.t0);
	intersection_arr_add(intersections, obj, calc.t1);
}

t_tuple	cone_local_normal_at(t_object *obj, t_tuple local_point)
{
	double	y;

	(void) obj;
	y = sqrt(pow(local_point.x, 2) + pow(local_point.z, 2));
	if (local_point.y > 0.0)
		y = -y;
	return (vector_create(local_point.x, y, local_point.z));
}

static void	cone_set_transformations(t_obj_transf *transformations,
	t_cone_data *data)
{
	t_tuple		default_axis;
	t_matrix	rotation;

	default_axis = (t_tuple){0, 1, 0, 0};
	rotation = align_axis(default_axis, data->axis);
	transformations->base = matrix_mult(
			rotation,
			matrix_scaling(data->radius, 1.0, data->radius));
	transformations->base = matrix_mult(
		matrix_translation(data->center.x, data->center.y, data->center.z),
		transformations->base);
	transformations->inverse = matrix_inverse(transformations->base);
	transformations->t_inverse = matrix_transpose(transformations->inverse);
}

char	*cone_init(t_object *object, t_cone_data *data, t_material *material)
{

	if (data->radius <= 0.0)
		return ("Cylinder: Invalid radius");
	object->data = malloc(sizeof(t_cone_data));
	*((t_cone_data *) object->data) = *data;
	cone_set_transformations(&object->transformations, data);
	object->material = *material;
	object->local_intersect = cone_intersect;
	object->local_normal_at = cone_local_normal_at;
	return (NULL);
}
