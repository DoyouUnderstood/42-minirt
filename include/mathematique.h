/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mathematique.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:01:48 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/16 15:40:03 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHEMATIQUE_H
# define MATHEMATIQUE_H

# include "../src/maths/maths.h"
# include "minilibx.h"
# include "object.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_sphere			t_sphere;
typedef struct s_intersection	t_intersection;
typedef struct s_shape			t_shape;
typedef struct s_mlx			t_mlx;
typedef struct s_material		t_material;
typedef struct s_object			t_object;

typedef struct s_ray
{
	t_tuple						origin;
	t_tuple						direction;
}	t_ray;

typedef t_tuple					(*t_local_normal_at)(t_shape *shape,
									t_tuple local_point);
typedef t_intersection			*(*t_local_intersect)(t_object *obj, t_ray *ray,
									int *count);

typedef struct s_shape
{
	t_matrix			transformation;
	t_material			*material;
	t_ray				saved_ray;
	t_local_normal_at	local_normal_at;
	t_local_intersect	local_intersect;
}	t_shape;

#endif