#include "../graphics/graphics.h"
#include "../include/shape.h"
#include "test_shape.h"
#include <stdlib.h>

// fonction intersect generalise
t_intersection	*intersect_shape(t_object *object, t_ray *ray, int *count)
{
	t_matrix	inverse_transform;
	t_ray		local_ray;

	*count = 0;
	inverse_transform = matrix_inverse(object->shape->transformation);
	local_ray = ray_transform(inverse_transform, *ray);
	return (object->shape->local_intersect(object, &local_ray, count));
}

// Fonction normal_at généralisée
t_tuple	normal_at_shape(t_object *obj, t_tuple world_point)
{
	t_tuple		local_point;
	t_tuple		local_normal;
	t_matrix	trans_inv;
	t_tuple		world_normal;

	local_point = matrix_mult(matrix_inverse(obj->shape->transformation),
			world_point);
	local_normal = obj->shape->local_normal_at(obj->shape, local_point);
	trans_inv = matrix_transpose(matrix_inverse(obj->shape->transformation));
	world_normal = matrix_mult(trans_inv, local_normal);
	world_normal.w = 0;
	return (vector_normalize(world_normal));
}

// fonction pour cree une intersection
t_intersection	intersection_create(double t, t_object *obj)
{
	t_intersection	i;

	i.t = t;
	i.obj = obj;
	return (i);
}

// Fonction pour identifier le hit parmi une collection d'intersections
t_intersection	*hit(t_intersection *intersections, int count)
{
	t_intersection	*hit;
	double			min_t;
	int				i;

	i = 0;
	hit = NULL;
	min_t = DBL_MAX;
	while (i < count)
	{
		if (intersections[i].t > 0 && intersections[i].t < min_t)
		{
			hit = &intersections[i];
			min_t = intersections[i].t;
		}
		i++;
	}
	return (hit);
}

t_color	calculate_color(t_intersection *closest_hit, t_ray *ray, t_light *light)
{
	t_lighting	lighting_params;

	if (closest_hit != NULL)
	{
		lighting_params.position = malloc(sizeof(t_tuple));
		if (lighting_params.position)
			*lighting_params.position = t_point_position(ray, closest_hit->t);
		lighting_params.normalv = malloc(sizeof(t_tuple));
		if (lighting_params.normalv)
		{
			*lighting_params.normalv = closest_hit->obj->shape->local_normal_at(closest_hit->obj->shape,
					*lighting_params.position);
		}
		lighting_params.eyev = malloc(sizeof(t_tuple));
		if (lighting_params.eyev)
			*lighting_params.eyev = vector_negate(ray->direction);
		lighting_params.material = closest_hit->obj->shape->material;
		lighting_params.object = closest_hit->obj;
		lighting_params.light = light;
		lighting_params.in_shadow = false;
		return (lighting(&lighting_params));
	}
	else
		return ((t_color){0, 0, 0});
}
