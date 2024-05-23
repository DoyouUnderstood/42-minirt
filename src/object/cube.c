/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:52:47 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/23 15:17:25 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "object.h"


#include <math.h>
#include <stdlib.h>

static t_cube_data	*cube_create_data(t_tuple center, double edge_len)
{
	t_cube_data	*cube_data;

	cube_data = malloc(sizeof(*cube_data));
	if (!cube_data)
		return (NULL);
	cube_data->center = center;
	cube_data->edge_len = edge_len;
	return (cube_data);
}

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

static t_tuple	cube_normal_at(t_shape *cube, t_tuple point)
{
	double	abs_x;
	double	abs_y;
	double	abs_z;
	double	maxc;

	(void)cube;
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

t_object	*cube_create(t_tuple center, double edge_length,
		t_material_specs specs)
{
	t_cube_data	*cube_data;
	t_shape		*shape;
	t_object	*obj;


	cube_data = cube_create_data(center, edge_length);
	shape = malloc(sizeof(t_shape));
	obj = malloc(sizeof(t_object));
	shape->transformation = matrix_translation(center.x, center.y, center.z);
	shape->transformation = matrix_mult(shape->transformation,
			matrix_scaling(edge_length / 2.0, edge_length / 2.0, edge_length / 2.0));
	shape->inv_transformation = matrix_inverse(shape->transformation);
	shape->tinv_transformation = matrix_transpose(shape->inv_transformation);
	shape->material = material_create_default(&specs.color, specs.reflectivity,
			specs.pattern);
	shape->material->reflectiv = specs.reflectivity;
	shape->local_intersect = cube_intersect;
	shape->local_normal_at = cube_normal_at;
	obj->type = CUBE;
	obj->data = cube_data;
	obj->shape = shape;
	return (obj);
}
