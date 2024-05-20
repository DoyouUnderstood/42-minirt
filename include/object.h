/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:07:46 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/20 13:47:12 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "color.h"
# include "mathematique.h"
# include "ray.h"
# include "shape.h"
# define EPSILON 0.00001

typedef struct s_shape			t_shape;
typedef struct s_ray			t_ray;
typedef struct s_color			t_color;
typedef struct s_pattern		t_pattern;
typedef struct s_material_specs	t_material_specs;
typedef struct s_cube
{
}	t_cube;


typedef enum e_obj_type
{
	SPHERE,
	CYLINDER,
	PLANE,
	CUBE,
	INVALID_TYPE
}	t_obj_type;

typedef struct s_object
{
	t_obj_type	type;
	void		*obj;
	t_shape		*shape;
}	t_object;

typedef struct s_plane
{
	t_tuple	center;
}	t_plane;

typedef struct s_cylinder
{
	t_tuple	center;
	t_tuple	axis;
	double	radius;
	double	height;
}	t_cylinder;

typedef struct s_camera
{
	double		hsize;
	double		vsize;
	double		fov;
	float		pixel_size;
	float		half_width;
	float		half_height;
	t_matrix	transform;
	t_tuple		position;
	t_tuple		direction;
}	t_camera;

t_object	*object_create_for_cylinder(t_tuple center,
				t_tuple axis, t_material_specs specs);

t_tuple		cube_local_normal_at(t_shape *cube, t_tuple point);

#endif