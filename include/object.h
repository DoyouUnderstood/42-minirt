/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:07:46 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/21 11:09:20 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "color.h"
# include "mathematique.h"
# include "ray.h"
# include "shape_old.h"
# define EPSILON 0.00001

typedef struct s_shape			t_shape;
typedef struct s_ray			t_ray;
typedef struct s_color			t_color;
typedef struct s_pattern		t_pattern;
typedef struct s_material_specs	t_material_specs;

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

#endif