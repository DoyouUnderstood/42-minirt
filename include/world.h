/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:33:47 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/21 18:23:29 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "camera.h"
# include "light.h"
# include "minilibx.h"
# include "object.h"

typedef struct s_mlx	t_mlx;

typedef struct s_world
{
	int						vsize;
	int						hsize;
	t_camera				*camera;
	t_mlx					*mlx;
	t_light					*light;
	t_object				**objects;
	int						object_count;
	t_amb_light				*amb;
}							t_world;

void					draw_render_to_img(t_world *world, t_mlx *mlx);
int						refresh_display(t_world *world);

#endif
