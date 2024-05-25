/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:53:16 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 04:45:03 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include "matrix.h"
#include "plane.h"
#include "object.h"
#include "utils.h"
#include "material.h"

#include <stdlib.h>

t_intersection	*plane_local_intersect(t_object *obj, t_ray *ray, int *count)
{
	double			t;
	t_intersection	*intersections;

	if (double_eq(ray->direction.y, 0.0))
	{
		*count = 0;
		return (NULL);
	}
	t = -ray->origin.y / ray->direction.y;
	*count = 1;
	intersections = intersection_create(obj, t);
	if (!intersections)
		*count = 0;
	return (intersections);
}

t_tuple	plane_local_normal_at(t_object *obj, t_tuple local_point)
{
	(void)local_point;
	(void)obj;
	return (vector_create(0, 1, 0));
}

// Intégration dans la création de l'objet Plane
t_object	*plane_create(t_plane_data *data, t_material *material)
{
	t_object	*obj;
	t_tuple		default_normal;
	t_matrix	rotation;
	t_matrix	translation;

	obj = (t_object *)malloc(sizeof(t_object));
	obj->data = malloc(sizeof(t_plane_data));
	obj->material = malloc(sizeof(t_material));
	*((t_plane_data *) obj->data) = *data;
	*obj->material = *material;
	default_normal = (t_tuple){0, 1, 0, 0};
	rotation = matrix_rotate_from_to(default_normal, data->direction);
	translation = matrix_translation(data->center.x, data->center.y, data->center.z);
	obj->transformation = matrix_mult(translation, rotation);
	obj->inv_transformation = matrix_inverse(obj->transformation);
	obj->tinv_transformation = matrix_transpose(obj->inv_transformation);
	obj->local_normal_at = plane_local_normal_at;
	obj->local_intersect = plane_local_intersect;
	return (obj);
}
