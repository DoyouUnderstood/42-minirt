/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:53:16 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/21 14:18:17 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include "matrix.h"
#include "plane.h"
#include "shape.h"
#include "utils.h"

static t_plane_data	*plane_create_data(t_tuple center)
{
	t_plane_data	*plane;

	plane = malloc(sizeof(t_plane_data));
	plane->center = center;
	return (plane);
}

t_tuple	plane_local_normal_at(t_shape *shape, t_tuple local_point)
{
	(void)local_point;
	(void)shape;
	return (vector_create(0, 1, 0));
}

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

// Intégration dans la création de l'objet Plane
t_object	*plane_create(t_color color, t_tuple center,
		t_pattern *pattern, t_tuple direction)
{
	t_plane_data		*plane;
	t_object	*obj;
	t_tuple		default_normal;
	t_matrix	rotation;
	t_matrix	translation;

	plane = plane_create_data(center);
	obj = (t_object *)malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->type = PLANE;
	obj->obj = plane;
	obj->shape = (t_shape *)malloc(sizeof(t_shape));
	default_normal = (t_tuple){0, 1, 0, 0};
	rotation = matrix_rotate_from_to(default_normal, direction);
	translation = matrix_translation(center.x, center.y, center.z);
	obj->shape->transformation = matrix_mult(translation, rotation);
	obj->shape->material = material_create_default_plane(&color, pattern);
	obj->shape->local_normal_at = plane_local_normal_at;
	obj->shape->local_intersect = plane_local_intersect;
	return (obj);
}
