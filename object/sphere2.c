/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:53:22 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/15 18:13:57 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics/graphics.h"
#include "../include/shape.h"
#include "../object/test_shape.h"
#include "test_shape.h"
#include <float.h>
#include <math.h>
#include <stdlib.h>

t_intersection	*local_intersect_sphere(t_object *obj, t_ray *ray,
		int *out_count)
{
	t_abcparams		abc_params;
	t_interparams	creation_params;
	double			discriminant;
	double			sqrt_discriminant;

	calculate_abc(ray, (t_sphere *)obj->obj, &abc_params);
	discriminant = calculate_discriminant(&abc_params);
	if (discriminant < -EPSILON)
	{
		*out_count = 0;
		return (NULL);
	}
	sqrt_discriminant = sqrt(discriminant);
	creation_params = (t_interparams){.t1 = (-abc_params.b
			- sqrt_discriminant) / (2 * abc_params.a), .t2 = (-abc_params.b
			+ sqrt_discriminant) / (2 * abc_params.a),
		.discriminant = discriminant, .obj = obj};
	return (create_intersections(&creation_params, out_count));
}

t_tuple	local_normal_at_sphere(t_shape *shape, t_tuple local_point)
{
	t_tuple	tupl;

	(void)shape;
	tupl = tuple_subtract(local_point, point_create(0, 0, 0));
	return (tupl);
}
