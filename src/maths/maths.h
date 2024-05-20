/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:25:14 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/16 16:30:30 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_H
# define MATHS_H

# include "color.h"
# include "matrix.h"
# include "../include/light.h"
# include "../include/mathematique.h"
# include "../include/minilibx.h"
# include "../include/pattern.h"
# include <stdbool.h>

typedef struct s_mlx	t_mlx;
typedef struct s_ray	t_ray;


// =========== RAY ============

t_ray					ray_create(t_tuple origin, t_tuple direction);
t_ray					ray_transform(t_matrix mat, t_ray ray);
t_tuple					t_point_position(const t_ray *ray, double t);
t_ray					ray_init(t_mlx *mlx, int x, int y,
							double projection_plane_z);



// ============== NORMAL ===============

t_tuple					reflect(t_tuple incident, t_tuple normal);

#endif