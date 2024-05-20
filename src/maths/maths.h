/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:25:14 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/20 12:01:50 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_H
# define MATHS_H

# include "color.h"
# include "matrix.h"
# include "ray.h"
# include "../include/light.h"
# include "../include/mathematique.h"
# include "../include/minilibx.h"
# include "../include/pattern.h"
# include <stdbool.h>

typedef struct s_mlx	t_mlx;


// =========== RAY ============

t_ray					ray_init(t_mlx *mlx, int x, int y,
							double projection_plane_z);



// ============== NORMAL ===============

t_tuple					reflect(t_tuple incident, t_tuple normal);

#endif