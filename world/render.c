#include "../include/main.h"
#include "../include/mathematique.h"
#include "../include/shape.h"
#include <math.h>
#include <stdio.h>
#include <pthread.h>

typedef struct 
{
    t_mlx *mlx;
    t_world *world;
    t_camera *camera;
    t_matrix inverse_transform;
    int start_y;
    int end_y;
} RenderThread;

// render fonction avec remaining pour nombre de reflect a calculer
void* render_section(void* arg) 
{
    RenderThread* data = (RenderThread*) arg;
    int remaining = 3;
    int x;
    int y;
    for (y = data->start_y; y < data->end_y; y++) {
        for (x = 0; x < data->world->camera->hsize; x++) {
            t_ray ray = ray_for_pixel(data->world->camera, &data->inverse_transform, x, y);
            t_color color = color_at(data->world, &ray, remaining);
            draw_pixel(data->mlx, x, y, color);
        }
    }
    return NULL;
}

void render(t_world *world) 
{
    const int num_threads = 40;
    pthread_t threads[num_threads];
    RenderThread thread_data[num_threads];
    t_matrix inverse_transform = matrix_inverse(world->camera->transform);
    int segment_height = world->camera->vsize / num_threads;
    int i;

    for (i = 0; i < num_threads; i++) {
        thread_data[i].mlx = world->mlx;
        thread_data[i].world = world;
        thread_data[i].camera = world->camera;
        thread_data[i].inverse_transform = inverse_transform;
        thread_data[i].start_y = i * segment_height;
        thread_data[i].end_y = (i == num_threads - 1) ? world->camera->vsize : (i + 1) * segment_height;

        pthread_create(&threads[i], NULL, render_section, &thread_data[i]);
    }
    for (i = 0; i < num_threads; i++)
        pthread_join(threads[i], NULL);
    draw_render_to_img(world, world->mlx);
}
