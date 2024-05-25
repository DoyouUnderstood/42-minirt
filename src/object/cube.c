/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:52:47 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 12:05:03 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

#include <math.h>
#include <stdlib.h>

static void	check_axis(double origin, double direction, double *tmin,
		double *tmax)
{
	double	tmin_numerator;
	double	tmax_numerator;
	double	temp;

	tmin_numerator = (-1 - origin);
	tmax_numerator = (1 - origin);
	if (fabs(direction) >= EPSILON)
	{
		*tmin = tmin_numerator / direction;
		*tmax = tmax_numerator / direction;
	}
	else
	{
		*tmin = tmin_numerator * INFINITY;
		*tmax = tmax_numerator * INFINITY;
	}
	if (*tmin > *tmax)
	{
		temp = *tmin;
		*tmin = *tmax;
		*tmax = temp;
	}
}

static t_intersection	*cube_intersect(t_object *obj, t_ray *ray, int *count)
{
	t_intersection	*intersections;
	double			tmin;
	double			tmax;
	double			bounds[6];

	check_axis(ray->origin.x, ray->direction.x, &bounds[0], &bounds[1]);
	check_axis(ray->origin.y, ray->direction.y, &bounds[2], &bounds[3]);
	check_axis(ray->origin.z, ray->direction.z, &bounds[4], &bounds[5]);
	tmin = fmax(fmax(bounds[0], bounds[2]), bounds[4]);
	tmax = fmin(fmin(bounds[1], bounds[3]), bounds[5]);
	if (tmin > tmax)
	{
		*count = 0;
		return (NULL);
	}
	*count = 2;
	intersections = intersection_create_pair(obj, tmin, tmax);
	if (!intersections)
		*count = 0;
	return (intersections);
}

static t_tuple	cube_normal_at(t_object *obj, t_tuple point)
{
	double	abs_x;
	double	abs_y;
	double	abs_z;
	double	maxc;

	(void) obj;
	abs_x = fabs(point.x);
	abs_y = fabs(point.y);
	abs_z = fabs(point.z);
	maxc = fmax(fmax(abs_x, abs_y), abs_z);
	if (maxc == abs_x)
		return ((t_tuple){copysign(1.0, point.x), 0, 0, 0});
	else if (maxc == abs_y)
		return ((t_tuple){0, copysign(1.0, point.y), 0, 0});
	else
		return ((t_tuple){0, 0, copysign(1.0, point.z), 0});
}

char	*cube_init(t_object *object, t_cube_data *data,
	t_material *material)
{
	if (data->edge_len <= 0.0)
		return ("Cube: Invalid edge length");
	object->data = malloc(sizeof(t_cube_data));
	*((t_cube_data *) object->data) = *data;
	object->material = *material;
	object->transformation = matrix_translation(data->center.x, data->center.y, data->center.z);
	object->transformation = matrix_mult(object->transformation,
			matrix_scaling(data->edge_len/ 2.0, data->edge_len/ 2.0, data->edge_len/ 2.0));
	object->inv_transformation = matrix_inverse(object->transformation);
	object->tinv_transformation = matrix_transpose(object->inv_transformation);
	object->local_intersect = cube_intersect;
	object->local_normal_at = cube_normal_at;
	return (NULL);
}
