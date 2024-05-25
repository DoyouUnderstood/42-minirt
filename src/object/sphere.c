/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:53:22 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 21:06:22 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object_internal.h"

#include <float.h>
#include <math.h>
#include <stdlib.h>

static void	set_intersections(t_sphere_intersect_calc *calc,
	t_intersection_pair *intersections)
{
	if (calc->discriminant < -EPSILON)
	{
		intersections->count = 0;
		return ;
	}
	calc->discriminant_sqrt = sqrt(calc->discriminant);
	calc->t0 = (-calc->b - calc->discriminant_sqrt) / (2 * calc->a),
	calc->t1 = (-calc->b + calc->discriminant_sqrt) / (2 * calc->a),
	intersections->t[0] = calc->t0;
	if (calc->discriminant == 0.0)
		intersections->count = 1;
	else
	{
		intersections->count = 2;
		intersections->t[1] = calc->t1;
	}
}

static void	sphere_intersect(t_object *obj, t_ray *ray,
	t_intersection_pair *intersections)
{
	t_sphere_intersect_calc	calc;
	static t_tuple			world_origin = {0, 0, 0, 0};

	intersections->obj = obj;
	calc.sphere_to_ray = tuple_subtract(ray->origin, world_origin);
	calc.a = vector_dot(ray->direction, ray->direction);
	calc.b = 2 * vector_dot(ray->direction, calc.sphere_to_ray);
	calc.c = vector_dot(calc.sphere_to_ray, calc.sphere_to_ray) - 1.0;
	calc.discriminant = calc.b * calc.b - 4 * calc.a * calc.c;
	set_intersections(&calc, intersections);
}

static t_tuple	sphere_normal_at(t_object *obj, t_tuple local_point)
{
	t_tuple	tupl;

	(void)obj;
	tupl = tuple_subtract(local_point, point_create(0, 0, 0));
	return (tupl);
}

static void	sphere_set_transformations(t_obj_transf *transformations,
	t_sphere_data *data)
{
	transformations->base = matrix_mult(
		matrix_translation(data->center.x, data->center.y, data->center.z),
		matrix_scaling(data->radius, data->radius, data->radius));
	transformations->inverse = matrix_inverse(transformations->base);
	transformations->t_inverse = matrix_transpose(transformations->inverse);
}

char	*sphere_init(t_object *object, t_sphere_data *data,
	t_material *material)
{
	if (data->radius <= 0.0)
		return ("Sphere: Invalid radius");
	object->data = malloc(sizeof(t_sphere_data));
	*((t_sphere_data *) object->data) = *data;
	sphere_set_transformations(&object->transformations, data);
	object->material = *material;
	object->local_intersect = sphere_intersect;
	object->local_normal_at = sphere_normal_at;
	return (NULL);
}
