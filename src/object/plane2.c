/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:53:16 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/16 15:40:52 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics/graphics.h"
#include "../include/shape.h"
#include "../object/test_shape.h"
#include "test_shape.h"
#include "utils.h"

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
	intersections = (t_intersection *)malloc(sizeof(t_intersection));
	if (!intersections)
	{
		*count = 0;
		return (NULL);
	}
	intersections[0] = (t_intersection){t, obj};
	return (intersections);
}
