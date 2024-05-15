#include "../include/main.h"
#include "../include/mathematique.h"
#include "../include/shape.h"
#include <math.h>
#include <pthread.h>
#include <stdio.h>

typedef struct s_renderthread
{
	t_mlx		*mlx;
	t_world		*world;
	t_camera	*camera;
	t_matrix	inverse_transform;
	int			start_y;
	int			end_y;
}				t_renderthread;

typedef struct {
    pthread_t *threads;
    t_renderthread *thread_data;
    t_matrix inverse_transform;
    int segment_height;
    int num_threads;
} RenderSetup;


void setup_thread_data(t_renderthread *thread_data, t_world *world, t_matrix inverse_transform, int i, int num_threads, int segment_height) {
    thread_data->mlx = world->mlx;
    thread_data->world = world;
    thread_data->camera = world->camera;
    thread_data->inverse_transform = inverse_transform;
    thread_data->start_y = i * segment_height;
    thread_data->end_y = (i == num_threads - 1) ? world->camera->vsize : (i + 1) * segment_height;
}

void initialize_and_launch_threads(RenderSetup *setup, t_world *world) 
{
    setup->inverse_transform = matrix_inverse(world->camera->transform);
    setup->segment_height = world->camera->vsize / setup->num_threads;

    for (int i = 0; i < setup->num_threads; i++) {
        setup_thread_data(&setup->thread_data[i], world, setup->inverse_transform, i, setup->num_threads, setup->segment_height);
        pthread_create(&setup->threads[i], NULL, render_section, &setup->thread_data[i]);
    }

    for (int i = 0; i < setup->num_threads; i++) {
        pthread_join(setup->threads[i], NULL);
    }
}


// render fonction avec remaining pour nombre de reflect a calculer
void	*render_section(void *arg)
{
	t_renderthread	*data;
	int				remaining;
	int				x;
	int				y;
	t_ray			ray;
	t_color			color;

	data = (t_renderthread *)arg;
	remaining = 2;
	for (y = data->start_y; y < data->end_y; y++)
	{
		for (x = 0; x < data->world->camera->hsize; x++)
		{
			ray = ray_for_pixel(data->world->camera, &data->inverse_transform,
					x, y);
			color = color_at(data->world, &ray, remaining);
			draw_pixel(data->mlx, x, y, color);
		}
	}
	return (NULL);
}

void render(t_world *world) {
    RenderSetup setup;
    setup.num_threads = 15; // Number of threads can be fixed or determined based on hardware capabilities
    setup.threads = malloc(setup.num_threads * sizeof(pthread_t));
    setup.thread_data = malloc(setup.num_threads * sizeof(t_renderthread));

    if (!setup.threads || !setup.thread_data) {
        free(setup.threads);   // Ensure proper resource management
        free(setup.thread_data);
        return; // Error handling
    }

    initialize_and_launch_threads(&setup, world);

    free(setup.threads);
    free(setup.thread_data);
    draw_render_to_img(world, world->mlx);
}

