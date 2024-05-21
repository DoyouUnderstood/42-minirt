/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_shape.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:53:25 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/21 05:25:19 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_SHAPE_H
# define TEST_SHAPE_H

# include "../include/object.h"
# include "../include/shape.h"

typedef struct s_ray	t_ray;
typedef struct s_shape	t_shape;
typedef struct s_object	t_object;
typedef struct s_plane	t_plane;

t_object				*object_create_for_plane(t_color color, t_tuple center,
							t_pattern *pattern, t_tuple dir);
t_plane					*plane_create(t_tuple center);
t_intersection			*plane_local_intersect(t_object *obj, t_ray *ray,
							int *count);
t_tuple					plane_local_normal_at(t_shape *shape,
							t_tuple local_point);
t_intersection			*intersect_shape(t_object *object, t_ray *ray,
							int *count);
t_tuple					normal_at_shape(t_object *obj, t_tuple world_point);

#endif