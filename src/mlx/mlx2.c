/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:37:57 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/21 18:22:54 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx.h"
#include "world.h"

#include <stdint.h>
#include <stdlib.h>

int	mlx_event_handle_keypress(t_mlx *mlx);

// fonction pour clean la mlx.
void	mlx_cleanup(t_mlx *mlx)
{
	if (mlx->img)
		mlx_destroy_image(mlx->ptr, mlx->img);
	if (mlx->win)
		mlx_destroy_window(mlx->ptr, mlx->win);
	if (mlx->ptr)
		free(mlx->ptr);
	free(mlx);
}

void	draw_render_to_img(t_world *world, t_mlx *mlx)
{
	mlx_hook(mlx->win, 17, 0L, mlx_event_close_win, mlx);
	mlx_loop_hook(mlx->ptr, refresh_display, world);
	mlx_key_hook(mlx->win, mlx_event_handle_keypress, mlx);
	mlx_loop(mlx->ptr);
}

int	refresh_display(t_world *world)
{
	mlx_put_image_to_window(world->mlx->ptr, world->mlx->win, world->mlx->img,
		0, 0);
	return (0);
}
