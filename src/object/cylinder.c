/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:53:12 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/27 12:51:48 by erabbath         ###   ########.fr       */
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

static void	cylinder_intersect(t_object *obj, t_ray *ray,
	t_intersection_arr *intersections)
{
	t_cylinder_data				*cylinder;
	t_cylinder_intersect_calc	calc;

	cylinder = (t_cylinder_data *) obj->data;
	calc.a = pow(ray->direction.x, 2) + pow(ray->direction.z, 2);
	calc.b = 2 * ray->origin.x * ray->direction.x
		+ 2 * ray->origin.z * ray->direction.z;
	calc.c = pow(ray->origin.x, 2) + pow(ray->origin.z, 2) - 1.0;
	calc.discriminant = pow(calc.b, 2) - 4 * calc.a * calc.c;
	if (fabs(calc.a) < EPSILON || calc.discriminant < -EPSILON)
		return ;
	calc.discriminant_sqrt = sqrt(calc.discriminant);
	calc.t0 = (-calc.b - calc.discriminant_sqrt) / (2 * calc.a);
	calc.t1 = (-calc.b + calc.discriminant_sqrt) / (2 * calc.a);
	calc.half_h = cylinder->height / 2.0;
	calc.y0 = ray->origin.y + calc.t0 * ray->direction.y;
	calc.y1 = ray->origin.y + calc.t1 * ray->direction.y;
	calc.t0_intersects = calc.y0 >= -calc.half_h && calc.y0 <= calc.half_h;
	calc.t1_intersects = calc.y1 >= -calc.half_h && calc.y1 <= calc.half_h;
	if (calc.t0_intersects)
		intersection_arr_add(intersections, obj, calc.t0);
	if (calc.t1_intersects)
		intersection_arr_add(intersections, obj, calc.t1);
}

t_tuple	cylinder_local_normal_at(t_object *obj, t_tuple local_point)
{
	(void) obj;
	return ((t_tuple){local_point.x, 0, local_point.z, 0});
}

static void	cylinder_set_transformations(t_obj_transf *transformations,
	t_cylinder_data *data)
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

char	*cylinder_init(t_object *object, t_cylinder_data *data, t_material *material)
{

	if (data->height <= 0.0)
		return ("Cylinder: Invalid height");
	if (data->radius <= 0.0)
		return ("Cylinder: Invalid radius");
	object->data = malloc(sizeof(t_cylinder_data));
	*((t_cylinder_data *) object->data) = *data;
	cylinder_set_transformations(&object->transformations, data);
	object->material = *material;
	object->local_intersect = cylinder_intersect;
	object->local_normal_at = cylinder_local_normal_at;
	return (NULL);
}
