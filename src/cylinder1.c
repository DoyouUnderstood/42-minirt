/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:53:12 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/21 09:21:11 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include "material.h"
#include "graphics.h"

#include <stdlib.h>

static t_cylinder_data	*create_cylinder_data(t_tuple center, double diameter, double height,
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

t_object	*cylinder_create(t_tuple center, t_tuple axis,
		t_material_specs specs)
{
	t_cylinder_data	*cylinder;
	t_object	*obj;
	t_tuple		default_axis;
	t_matrix	rotation;

	cylinder = create_cylinder_data(center, specs.diameter, specs.height, axis);
	obj = malloc(sizeof(t_object));
	obj->type = CYLINDER;
	obj->obj = cylinder;
	obj->shape = malloc(sizeof(t_shape));
	default_axis = (t_tuple){0, 1, 0, 0};
	rotation = align_axis(default_axis, axis);
	obj->shape->transformation = matrix_mult(matrix_translation(center.x,
				center.y, center.z), rotation);
	obj->shape->material = material_create_default(&specs.color,
			specs.reflectivity, specs.pattern);
	obj->shape->local_intersect = cylinder_intersect;
	obj->shape->local_normal_at = cylinder_local_normal_at;
	return (obj);
}

t_tuple	cylinder_local_normal_at(t_shape *shape, t_tuple local_point)
{
	(void)shape;
	return ((t_tuple){local_point.x, 0, local_point.z, 0});
}
