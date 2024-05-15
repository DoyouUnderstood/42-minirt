#include "../include/main.h"
#include "../include/mathematique.h"
#include "../include/shape.h"
#include <math.h>
#include <pthread.h>
#include <stdio.h>

typedef struct s_renderthread
{
	t_mlx			*mlx;
	t_world			*world;
	t_camera		*camera;
	t_matrix		inverse_transform;
	int				start_y;
	int				end_y;
}					t_renderthread;

typedef struct s_RenderSetup
{
	pthread_t		*threads;
	t_renderthread	*thread_data;
	t_matrix		inverse_transform;
	int				segment_height;
	int				num_threads;
	int				current_index;
}					t_RenderSetup;

typedef struct	s_threadSetupParams
{
	t_renderthread	*thread_data;
	t_world			*world;
	t_matrix		inverse_transform;
	int				index;
	int				num_threads;
	int				segment_height;
}					t_threadSetupParams;

void	setup_thread_data(t_threadSetupParams *params)
{
	params->thread_data->mlx = params->world->mlx;
	params->thread_data->world = params->world;
	params->thread_data->camera = params->world->camera;
	params->thread_data->inverse_transform = params->inverse_transform;
	params->thread_data->start_y = params->index * params->segment_height;
	params->thread_data->end_y = (params->index == params->num_threads
			- 1) ? params->world->camera->vsize : (params->index + 1)
		* params->segment_height;
}

// render fonction avec remaining pour nombre de reflect a calculer
void	*render_section(void *arg)
{
	t_renderthread	*data;
	int				remaining;
	t_ray			ray;
	t_color			color;

	data = (t_renderthread *)arg;
	remaining = 2;
	for (int y = data->start_y; y < data->end_y; y++)
	{
		for (int x = 0; x < data->world->camera->hsize; x++)
		{
			ray = ray_for_pixel(data->world->camera, &data->inverse_transform,
					x, y);
			color = color_at(data->world, &ray, remaining);
			draw_pixel(data->mlx, x, y, color);
		}
	}
	return (NULL);
}

void	initialize_and_launch_threads(t_RenderSetup *setup, t_world *world)
{
	t_threadSetupParams	params;

	setup->inverse_transform = matrix_inverse(world->camera->transform);
	setup->segment_height = world->camera->vsize / setup->num_threads;
	for (int i = 0; i < setup->num_threads; i++)
	{
		params = (t_threadSetupParams){.thread_data = &setup->thread_data[i],
			.world = world, .inverse_transform = setup->inverse_transform,
			.index = i, .num_threads = setup->num_threads,
			.segment_height = setup->segment_height};
		setup_thread_data(&params);
		pthread_create(&setup->threads[i], NULL, render_section,
			&setup->thread_data[i]);
	}
	for (int i = 0; i < setup->num_threads; i++)
	{
		pthread_join(setup->threads[i], NULL);
	}
}

void	render(t_world *world)
{
	t_RenderSetup	setup;

	setup.num_threads = 15;
	// Number of threads can be fixed or determined based on hardware capabilities
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
