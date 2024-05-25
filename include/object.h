/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:07:46 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 09:49:37 by erabbath         ###   ########.fr       */
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

typedef struct s_object
{
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

#endif