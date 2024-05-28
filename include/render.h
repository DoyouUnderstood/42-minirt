/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:26:50 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/28 12:06:13 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "minilibx.h"
# include "world.h"
# include "camera.h"
# include "matrix.h"

# include <pthread.h>

# define THREAD_COUNT 15

typedef struct s_renderthread
{
	t_mlx					*mlx;
	t_world					*world;
	t_camera				*camera;
	t_matrix				inverse_transform;
	int						start_y;
	int						end_y;
}							t_renderthread;

typedef struct s_RenderSetup
{
	pthread_t				threads[THREAD_COUNT];
	t_renderthread			thread_data[THREAD_COUNT];
	t_matrix				inverse_transform;
	int						segment_height;
	int						num_threads;
	int						current_index;
}							t_RenderSetup;

typedef struct s_threadSetupParams
{
	t_renderthread			*thread_data;
	t_world					*world;
	t_matrix				inverse_transform;
	int						index;
	int						num_threads;
	int						segment_height;
}							t_threadSetupParams;

#endif