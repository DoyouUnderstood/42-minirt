/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:53:12 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/21 09:18:03 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include "utils.h"

t_intersection	*create_intersections(t_cylinder_intersect_data *data, t_object *obj, int *count)
{
	t_intersection	*intersections;
	bool			t0_intersects;
	bool			t1_intersects;

	t0_intersects = data->y0 >= -data->half_height && data->y0 <= data->half_height;
	t1_intersects = data->y1 >= -data->half_height && data->y1 <= data->half_height;
	intersections = NULL;
	if (t0_intersects && t1_intersects && !double_eq(data->t0, data->t1))
	{
		*count = 2;
		intersections = intersection_create_pair(obj, data->t0, data->t1);
	}
	else if (t0_intersects)
	{
		*count = 1;
		intersections = intersection_create(obj, data->t0);
	}
	else if (t1_intersects)
	{
		*count = 1;
		intersections = intersection_create(obj, data->t1);
	}
	if (!intersections)
		*count = 0;
	return (intersections);
}

t_intersection	*cylinder_intersect(t_object *obj, t_ray *ray, int *count)
{
	t_cylinder_data				*cylinder;
	t_cylinder_intersect_data	data;

	cylinder = (t_cylinder_data *) obj->obj;
	data.a = pow(ray->direction.x, 2) + pow(ray->direction.z, 2);
	data.b = 2 * ray->origin.x * ray->direction.x + 2 * ray->origin.z * ray->direction.z;
	data.c = pow(ray->origin.x, 2) + pow(ray->origin.z, 2) - pow(cylinder->radius, 2);
	data.discriminant = pow(data.b, 2) - 4 * data.a * data.c;
	if (fabs(data.a) < EPSILON || data.discriminant < -EPSILON)
	{
		*count = 0;
		return (NULL);
	}
	data.discriminant_sqrt = sqrt(data.discriminant);
	data.t0 = (-data.b - data.discriminant_sqrt) / (2 * data.a);
	data.t1 = (-data.b + data.discriminant_sqrt) / (2 * data.a);
	data.half_height = cylinder->height / 2.0;
	data.y0 = ray->origin.y + data.t0 * ray->direction.y;
	data.y1 = ray->origin.y + data.t1 * ray->direction.y;
	return (create_intersections(&data, obj, count));
}
