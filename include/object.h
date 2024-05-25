/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:07:46 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 21:21:17 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "color.h"
# include "material.h"
# include "pattern.h"
# include "ray.h"
# include "intersection.h"

# define MAX_OBJECTS 30
# define EPSILON 0.00001

typedef struct s_object				t_object;
typedef struct s_intersection		t_intersection;
typedef struct s_intersection_pair	t_intersection_pair;

typedef void	(*t_local_intersect)(t_object *obj, t_ray *ray,
					t_intersection_pair *intersections);
typedef t_tuple	(*t_local_normal_at)(t_object *obj, t_tuple local_point);

typedef struct s_obj_transf
{
	t_matrix	base;
	t_matrix	inverse;
	t_matrix	t_inverse;
}	t_obj_transf;

typedef struct s_object
{
	void				*data;
	t_obj_transf		transformations;
	t_material			material;
	t_ray				saved_ray;
	t_local_normal_at	local_normal_at;
	t_local_intersect	local_intersect;
}	t_object;

typedef struct s_sphere_data
{
	t_tuple	center;
	double	radius;
}	t_sphere_data;

typedef struct s_cylinder_data
{
	t_tuple	center;
	t_tuple	axis;
	double	radius;
	double	height;
}	t_cylinder_data;

typedef struct s_cube_data
{
	t_tuple	center;
	double	edge_len;
}	t_cube_data;

typedef struct s_plane_data
{
	t_tuple	center;
	t_tuple	direction;
}	t_plane_data;

char			*sphere_init(t_object *object, t_sphere_data *data,
					t_material *material);
char			*cylinder_init(t_object *object, t_cylinder_data *data,
					t_material *material);
char			*cube_init(t_object *object, t_cube_data *data,
					t_material *material);
char			*plane_init(t_object *object, t_plane_data *data,
					t_material *material);

t_intersection	*object_intersect(t_object *object, t_ray *ray,
					int *count);
t_tuple			object_normal_at(t_object *obj, t_tuple world_point);

#endif