/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:53:16 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/26 18:33:10 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include "matrix.h"
#include "object.h"
#include "utils.h"
#include "material.h"

#include <stdlib.h>

static void	plane_local_intersect(t_object *obj, t_ray *ray,
	t_intersection_arr *intersections)
{
	double			t;

	if (double_eq(ray->direction.y, 0.0))
		return ;
	t = -ray->origin.y / ray->direction.y;
	intersection_arr_add(intersections, obj, t);
}

t_tuple	plane_local_normal_at(t_object *obj, t_tuple local_point)
{
	(void)local_point;
	(void)obj;
	return (vector_create(0, 1, 0));
}

static void	plane_set_transformations(t_obj_transf *transformations,
	t_plane_data *data)
{
	t_tuple		default_normal;
	t_matrix	rotation;
	t_matrix	translation;

	default_normal = (t_tuple){0, 1, 0, 0};
	rotation = matrix_rotate_from_to(default_normal, data->direction);
	translation = matrix_translation(data->center.x, data->center.y, data->center.z);
	transformations->base = matrix_mult(translation, rotation);
	transformations->inverse = matrix_inverse(transformations->base);
	transformations->t_inverse = matrix_transpose(transformations->inverse);
}

// Intégration dans la création de l'objet Plane
char	*plane_init(t_object *object, t_plane_data *data, t_material *material)
{
	object->data = malloc(sizeof(t_plane_data));
	*((t_plane_data *) object->data) = *data;
	plane_set_transformations(&object->transformations, data);
	object->material = *material;
	object->local_normal_at = plane_local_normal_at;
	object->local_intersect = plane_local_intersect;
	return (NULL);
}
