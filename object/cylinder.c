#include "../graphics/graphics.h"
#include "../include/shape.h"
#include "../object/test_shape.h"
#include "test_shape.h"
#include <float.h>
#include <math.h>
#include <stdlib.h>

t_cylinder	*create_cylinder(t_tuple center, double diameter, double height,
		t_tuple axis)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (NULL);
	cylinder->center = center;
	cylinder->axis = axis;
	cylinder->radius = diameter / 2.0;
	cylinder->height = height;
	return (cylinder);
}

t_matrix	align_axis(t_tuple default_axis, t_tuple new_axis)
{
	t_tuple	axis;
	double	dot_product;
	double	angle;

	axis = vector_cross(default_axis, new_axis);
	dot_product = vector_dot(vector_normalize(default_axis),
			vector_normalize(new_axis));
	angle = acos(dot_product);
	return (matrix_rotation_axis(axis, angle));
}

t_object	*object_create_for_cylinder(t_tuple center, t_tuple axis,
		t_material_specs specs)
{
	t_cylinder	*cylinder;
	t_object	*obj;
	t_tuple		default_axis;
	t_matrix	rotation;

	cylinder = create_cylinder(center, specs.diameter, specs.height, axis);
	obj = malloc(sizeof(t_object));
	obj->type = CYLINDER;
	obj->obj = cylinder;
	obj->shape = malloc(sizeof(t_shape));
	default_axis = (t_tuple){0, 1, 0, 0};
	rotation = align_axis(default_axis, axis);
	obj->shape->transformation = matrix_multiply(matrix_translation(center.x,
				center.y, center.z), rotation);
	obj->shape->material = material_create_default(&specs.color,
			specs.reflectivity, specs.pattern);
	obj->shape->local_intersect = cylinder_intersect;
	obj->shape->local_normal_at = cylinder_local_normal_at;
	return (obj);
}

t_tuple	cylinder_local_normal_at(t_shape *shape, t_tuple local_point)
{
	(void)shape;
	return ((t_tuple){local_point.x, 0, local_point.z, 0});
}

typedef struct s_intersectionParams
{
	double					a;
	double					b;
	double					c;
	double					discriminant;
	double					t0;
	double					t1;
	double					half_height;
}							t_intersectionParams;

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

typedef struct s_interesctionData
{
	double					y0;
	double					y1;
	double					half_height;
	t_intersectionParams	*p;
	t_object				*obj;
}							t_interesctionData;

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
