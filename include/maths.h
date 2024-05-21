/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:25:14 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/21 14:15:02 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_H
# define MATHS_H

# include "color.h"
# include "matrix.h"
# include "ray.h"
# include "light.h"
# include "minilibx.h"
# include "pattern.h"

# include <stdbool.h>

// =========== RAY ============

t_ray	ray_init(t_mlx *mlx, int x, int y,
			double projection_plane_z);
// ============== NORMAL ===============

t_tuple	reflect(t_tuple incident, t_tuple normal);

#endif