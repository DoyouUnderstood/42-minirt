/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:17:34 by ltd               #+#    #+#             */
/*   Updated: 2024/05/21 14:16:22 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "shape_old.h"
#include "world.h"

#include <math.h>
#include <stdio.h>

void	setup_thread_data(t_threadSetupParams *params);

void	process_x(t_renderthread *data, int x, int y, int remaining)
{
	t_ray	ray;
	t_color	color;

	if (x < data->world->camera->hsize)
	{
		ray = ray_for_pixel(data->world->camera, &data->inverse_transform, x,
				y);
		color = color_at(data->world, &ray, remaining);
		draw_pixel(data->mlx, x, y, color);
		process_x(data, x + 1, y, remaining);
	}
}

void	process_y(t_renderthread *data, int y, int remaining)
{
	if (y < data->end_y)
	{
		process_x(data, 0, y, remaining);
		process_y(data, y + 1, remaining);
	}
}

// render fonction avec remaining pour nombre de reflect a calculer
void	*render_section(void *arg)
{
	t_renderthread	*data;
	int				remaining;

	data = (t_renderthread *)arg;
	remaining = 5;
	process_y(data, data->start_y, remaining);
	return (NULL);
}

void	initialize_and_launch_threads(t_RenderSetup *setup, t_world *world)
{
	t_threadSetupParams	params;
	int					i;

	i = 0;
	setup->inverse_transform = matrix_inverse(world->camera->transform);
	setup->segment_height = world->camera->vsize / setup->num_threads;
	while (i < setup->num_threads)
	{
		params = (t_threadSetupParams){.thread_data = &setup->thread_data[i],
			.world = world, .inverse_transform = setup->inverse_transform,
			.index = i, .num_threads = setup->num_threads,
			.segment_height = setup->segment_height};
		setup_thread_data(&params);
		pthread_create(&setup->threads[i], NULL, render_section,
			&setup->thread_data[i]);
		i++;
	}
	i = 0;
	while (i < setup->num_threads)
	{
		pthread_join(setup->threads[i], NULL);
		i++;
	}
}

void	render(t_world *world)
{
	t_RenderSetup	setup;

	setup.num_threads = 15;
	setup.threads = malloc(setup.num_threads * sizeof(pthread_t));
	setup.thread_data = malloc(setup.num_threads * sizeof(t_renderthread));
	if (!setup.threads || !setup.thread_data)
	{
		free(setup.threads);
		free(setup.thread_data);
		return ;
	}
	initialize_and_launch_threads(&setup, world);
	free(setup.threads);
	free(setup.thread_data);
	draw_render_to_img(world, world->mlx);
}
