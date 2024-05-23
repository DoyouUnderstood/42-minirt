/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:07:46 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/23 15:31:43 by erabbath         ###   ########.fr       */
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

typedef struct s_object			t_object;
typedef struct s_intersection	t_intersection;

typedef t_intersection	*(*t_local_intersect)(t_object *obj, t_ray *ray,
							int *count);
typedef t_tuple			(*t_local_normal_at)(t_object *obj, t_tuple local_point);

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
	t_obj_type			type;
	void				*data;
	t_matrix			transformation;
	t_matrix			inv_transformation;
	t_matrix			tinv_transformation;
	t_material			*material;
	t_ray				saved_ray;
	t_local_normal_at	local_normal_at;
	t_local_intersect	local_intersect;
}	t_object;

t_intersection	*object_intersect(t_object *object, t_ray *ray,
					int *count);
t_tuple			object_normal_at(t_object *obj, t_tuple world_point);

t_color			stripe_at_object(const t_pattern *pattern,
					const t_object *object, t_tuple point);

#endif