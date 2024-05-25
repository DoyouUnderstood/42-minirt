/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:53:16 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 11:45:25 by erabbath         ###   ########.fr       */
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
char	*plane_init(t_object *object, t_plane_data *data, t_material *material)
{
	t_tuple		default_normal;
	t_matrix	rotation;
	t_matrix	translation;

	object->data = malloc(sizeof(t_plane_data));
	*((t_plane_data *) object->data) = *data;
	object->material = *material;
	default_normal = (t_tuple){0, 1, 0, 0};
	rotation = matrix_rotate_from_to(default_normal, data->direction);
	translation = matrix_translation(data->center.x, data->center.y, data->center.z);
	object->transformation = matrix_mult(translation, rotation);
	object->inv_transformation = matrix_inverse(object->transformation);
	object->tinv_transformation = matrix_transpose(object->inv_transformation);
	object->local_normal_at = plane_local_normal_at;
	object->local_intersect = plane_local_intersect;
	return (NULL);
}
