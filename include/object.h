/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:07:46 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/23 15:15:56 by erabbath         ###   ########.fr       */
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

struct s_shape;
struct s_object;
typedef struct s_intersection	t_intersection;

typedef t_tuple			(*t_local_normal_at)(struct s_shape *shape,
							t_tuple local_point);
typedef t_intersection	*(*t_local_intersect)(struct s_object *obj, t_ray *ray,
							int *count);

typedef struct s_shape
{
	t_matrix			transformation;
	t_matrix			inv_transformation;
	t_matrix			tinv_transformation;
	t_material			*material;
	t_ray				saved_ray;
	t_local_normal_at	local_normal_at;
	t_local_intersect	local_intersect;
}	t_shape;

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
	void		*data;
	t_shape		*shape;
}	t_object;

t_intersection	*intersect_shape(t_object *object, t_ray *ray,
					int *count);
t_tuple			normal_at_shape(t_object *obj, t_tuple world_point);

t_color			stripe_at_object(const t_pattern *pattern,
					const t_object *object, t_tuple point);

#endif