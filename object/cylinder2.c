/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:53:12 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/15 18:16:06 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics/graphics.h"
#include "../include/shape.h"
#include "../object/test_shape.h"
#include "test_shape.h"
#include <float.h>
#include <math.h>
#include <stdlib.h>

void	init_intersection_params(t_intersectionParams *p, t_ray *ray,
		t_cylinder *cylinder)
{
	p->a = pow(ray->direction.x, 2) + pow(ray->direction.z, 2);
	p->b = 2 * ray->origin.x * ray->direction.x + 2 * ray->origin.z
		* ray->direction.z;
	p->c = pow(ray->origin.x, 2) + pow(ray->origin.z, 2) - pow(cylinder->radius,
			2);
	p->discriminant = pow(p->b, 2) - 4 * p->a * p->c;
}

bool	check_intersection_range(double y0, double y1, double half_height)
{
	if ((y0 < -half_height || y0 > half_height) && (y1 < -half_height
			|| y1 > half_height))
		return (false);
	return (true);
}

t_intersection	*allocate_fill_intersections(t_interesctionData *data,
		int *count)
{
	t_intersection	*intersections;

	intersections = malloc(2 * sizeof(t_intersection));
	if (!intersections)
	{
		*count = 0;
		return (NULL);
	}
	*count = 0;
	if (!(data->y0 < -data->half_height || data->y0 > data->half_height))
	{
		intersections[*count] = (t_intersection){data->p->t0, data->obj};
		(*count)++;
	}
	if (!(data->y1 < -data->half_height || data->y1 > data->half_height)
		&& data->p->t0 != data->p->t1)
	{
		intersections[*count] = (t_intersection){data->p->t1, data->obj};
		(*count)++;
	}
	return (intersections);
}

t_intersection	*cylinder_intersect(t_object *obj, t_ray *ray, int *count)
{
	t_intersectionParams	p;
	double					half_height;
	double					y0;
	double					y1;
	t_interesctionData		data;

	init_intersection_params(&p, ray, (t_cylinder *)obj->obj);
	if (fabs(p.a) < EPSILON || p.discriminant < 0)
	{
		*count = 0;
		return (NULL);
	}
	p.t0 = (-p.b - sqrt(p.discriminant)) / (2 * p.a);
	p.t1 = (-p.b + sqrt(p.discriminant)) / (2 * p.a);
	half_height = ((t_cylinder *)obj->obj)->height / 2.0;
	y0 = ray->origin.y + p.t0 * ray->direction.y;
	y1 = ray->origin.y + p.t1 * ray->direction.y;
	data = (t_interesctionData){y0, y1, half_height, &p, obj};
	if ((y0 < -half_height || y0 > half_height) && (y1 < -half_height
			|| y1 > half_height))
	{
		*count = 0;
		return (NULL);
	}
	return (allocate_fill_intersections(&data, count));
}
