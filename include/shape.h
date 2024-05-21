/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:53:25 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/21 14:07:30 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H

# include "intersection.h"
# include "material.h"
# include "object.h"
# include "ray.h"
# include "tuple.h"

typedef t_tuple			(*t_local_normal_at)(t_shape *shape,
							t_tuple local_point);
typedef t_intersection	*(*t_local_intersect)(t_object *obj, t_ray *ray,
							int *count);

typedef struct s_shape
{
	t_matrix			transformation;
	t_material			*material;
	t_ray				saved_ray;
	t_local_normal_at	local_normal_at;
	t_local_intersect	local_intersect;
}	t_shape;

t_intersection			*intersect_shape(t_object *object, t_ray *ray,
							int *count);
t_tuple					normal_at_shape(t_object *obj, t_tuple world_point);

#endif