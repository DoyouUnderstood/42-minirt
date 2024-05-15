/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:07:41 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/15 17:37:45 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINILIBX_H
# define MINILIBX_H

# include "../lib/mlx/mlx.h"
# include "main.h"

# define KEY_ESC 'e'

typedef struct s_color	t_color;
typedef struct s_world	t_world;

typedef struct s_mlx
{
	void				*ptr;
	void				*win;
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	int					width;
	int					height;
	void				*menu;
}						t_mlx;

// ============= FONCTION MLX ================

void					mlx_put_pixel_to_img(t_mlx *mlx, int x, int y,
							int color);
int						mlx_create_image(t_mlx *mlx, int width, int height);
t_mlx					*mlx_init_and_create_window(int width, int height,
							char *title);
void					mlx_cleanup(t_mlx *mlx);
int						mlx_event_close_win(t_mlx *mlx);
void					draw_pixel(t_mlx *mlx, int x, int y, t_color color);
void					draw_render_to_img(t_world *world, t_mlx *mlx);
int						refresh_display(t_world *world);

#endif
