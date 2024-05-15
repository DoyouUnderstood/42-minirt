#include "../graphics/graphics.h"
#include "../include/shape.h"
#include "../object/test_shape.h"
#include "test_shape.h"

// Création d'une matrice de rotation autour d'un axe par un angle
t_matrix	matrix_rotation_axis(t_tuple axis, double angle)
{
	double		cos_theta;
	double		sin_theta;
	double		one_minus_cos;
	t_matrix	rot;

	axis = vector_normalize(axis);
	cos_theta = cos(angle);
	sin_theta = sin(angle);
	one_minus_cos = 1.0 - cos_theta;
	rot.m[0][0] = cos_theta + axis.x * axis.x * one_minus_cos;
	rot.m[0][1] = axis.x * axis.y * one_minus_cos - axis.z * sin_theta;
	rot.m[0][2] = axis.x * axis.z * one_minus_cos + axis.y * sin_theta;
	rot.m[0][3] = 0;
	rot.m[1][0] = axis.y * axis.x * one_minus_cos + axis.z * sin_theta;
	rot.m[1][1] = cos_theta + axis.y * axis.y * one_minus_cos;
	rot.m[1][2] = axis.y * axis.z * one_minus_cos - axis.x * sin_theta;
	rot.m[1][3] = 0;
	rot.m[2][0] = axis.z * axis.x * one_minus_cos - axis.y * sin_theta;
	rot.m[2][1] = axis.z * axis.y * one_minus_cos + axis.x * sin_theta;
	rot.m[2][2] = cos_theta + axis.z * axis.z * one_minus_cos;
	rot.m[2][3] = 0;
	rot.m[3][0] = 0;
	rot.m[3][1] = 0;
	rot.m[3][2] = 0;
	rot.m[3][3] = 1;
	return (rot);
}

t_material		*material_create_default_plane(t_color *color,
				t_pattern *pattern);

// Utilitaire pour calculer la matrice de rotation d'un vecteur à un autre
t_matrix	rotate_from_to(t_tuple from, t_tuple to)
{
	t_tuple	axis;
	double	angle;

	axis = vector_cross(from, to);
	angle = acos(vector_dot(vector_normalize(from), vector_normalize(to)));
	return (matrix_rotation_axis(axis, angle));
}

// Intégration dans la création de l'objet Plane
t_object	*object_create_for_plane(t_color color, t_tuple center,
		t_pattern *pattern, t_tuple direction)
{
	t_plane		*plane;
	t_object	*obj;
	t_tuple		default_normal;
	t_matrix	rotation;
	t_matrix	translation;

	plane = plane_create(center);
	obj = (t_object *)malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->type = PLANE;
	obj->obj = plane;
	obj->shape = (t_shape *)malloc(sizeof(t_shape));
	default_normal = (t_tuple){0, 1, 0, 0};
	rotation = rotate_from_to(default_normal, direction);
	translation = matrix_translation(center.x, center.y, center.z);
	obj->shape->transformation = matrix_multiply(translation, rotation);
	obj->shape->material = material_create_default_plane(&color, pattern);
	obj->shape->local_normal_at = plane_local_normal_at;
	obj->shape->local_intersect = plane_local_intersect;
	return (obj);
}

t_plane	*plane_create(t_tuple center)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	plane->center = center;
	return (plane);
}

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

	if (fabs(ray->direction.y) < TUPLE_EPSILON)
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
