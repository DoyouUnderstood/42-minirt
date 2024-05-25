/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:52:47 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 21:21:55 by erabbath         ###   ########.fr       */
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

static void	cube_intersect(t_object *obj, t_ray *ray,
	t_intersection_pair *intersections)
{
	double			tmin;
	double			tmax;
	double			bounds[6];

	intersections->obj = obj;
	intersections->count = 0;
	check_axis(ray->origin.x, ray->direction.x, &bounds[0], &bounds[1]);
	check_axis(ray->origin.y, ray->direction.y, &bounds[2], &bounds[3]);
	check_axis(ray->origin.z, ray->direction.z, &bounds[4], &bounds[5]);
	tmin = fmax(fmax(bounds[0], bounds[2]), bounds[4]);
	tmax = fmin(fmin(bounds[1], bounds[3]), bounds[5]);
	if (tmin > tmax)
		return ;
	intersections->count = 2;
	intersections->t[0] = tmin;
	intersections->t[1] = tmax;
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

static void	cube_set_transformations(t_obj_transf *transformations,
	t_cube_data *data)
{
	transformations->base
		= matrix_translation(data->center.x, data->center.y, data->center.z);
	transformations->base = matrix_mult(transformations->base,
			matrix_scaling(data->edge_len/ 2.0, data->edge_len/ 2.0, data->edge_len/ 2.0));
	transformations->inverse = matrix_inverse(transformations->base);
	transformations->t_inverse = matrix_transpose(transformations->inverse);

}

char	*cube_init(t_object *object, t_cube_data *data,
	t_material *material)
{
	if (data->edge_len <= 0.0)
		return ("Cube: Invalid edge length");
	object->data = malloc(sizeof(t_cube_data));
	*((t_cube_data *) object->data) = *data;
	cube_set_transformations(&object->transformations, data);
	object->material = *material;
	object->local_intersect = cube_intersect;
	object->local_normal_at = cube_normal_at;
	return (NULL);
}
