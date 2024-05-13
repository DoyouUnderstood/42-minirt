#include "../include/minilibx.h"
#include <stdint.h>
#include "../graphics/graphics.h"

#include <stdlib.h>

// void error_exit(char *error_message) {
//     fprintf(stderr, "%s", error_message);
//     exit(EXIT_FAILURE);
// }

// Initialisation de MLX en utilisant la structure t_world
// fonction pour cree une image.
int mlx_create_image(t_mlx *mlx, int width, int height) {
    mlx->img = mlx_new_image(mlx->ptr, width, height);
    if (!mlx->img)
        error_exit("Erreur lors de la création de l'image\n");

    mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
    return 1;
}


void mlx_initialisation(t_world *world) {
    world->mlx = malloc(sizeof(t_mlx));
    if (!world->mlx)
        error_exit("Erreur allocation mémoire pour mlx\n");

    world->mlx->ptr = mlx_init();
    if (!world->mlx->ptr)
        error_exit("Erreur initialisation mlx\n");

    printf("Resolution : %d\n%d", world->hsize, world->vsize);
    world->mlx->win = mlx_new_window(world->mlx->ptr, world->hsize, world->vsize, "minirt");
    if (!world->mlx->win)
        error_exit("Erreur lors de la création de la fenêtre\n");

    // Utiliser la fonction mlx_create_image pour créer et configurer l'image
    if (!mlx_create_image(world->mlx, world->hsize, world->vsize)) {
        error_exit("Failed to create and configure the image\n");
    }
}




// fonction pour initialiser un windows.
t_mlx   *mlx_init_and_create_window(int width, int height, char *title)
{
    t_mlx   *mlx;

    mlx = (t_mlx *)malloc(sizeof(t_mlx));
    mlx->ptr = mlx_init();
    if (!mlx->ptr)
    {
        free(mlx);
        error_exit("erreur initialisation mlx\nmlx.c l15\n");
    }
    mlx->win = mlx_new_window(mlx->ptr, width, height, title);
    if (!mlx->win)
    {
        free(mlx);
        error_exit("erreur creation windows mlx \nmlx.c l21\n");
    }
    mlx->img = NULL;
    mlx->width = width;
    mlx->height = height;
    return (mlx);
}


// fonction pour ajouter un pixel dans l'image
void mlx_put_pixel_to_img(t_mlx *mlx, int x, int y, int color) 
{
    if (!mlx || !mlx->addr)
        error_exit("Mlx or mlx->addr is null\n");

    // if (x < 0 || x >= mlx->width || y < 0 || y >= mlx->height)
    //     error_exit("Pixel coordinates out of bounds\n");

    int bytes_per_pixel = mlx->bits_per_pixel / 8;
    
    if (bytes_per_pixel != 4) // Assumer que chaque pixel prend 4 octets (32 bits)
        error_exit("Unexpected bits per pixel\n");

    int pixel_index = (y * mlx->line_length) + (x * bytes_per_pixel);
    *(unsigned int*)(mlx->addr + pixel_index) = mlx_get_color_value(mlx->ptr, color);
}



void draw_pixel(t_mlx *mlx, int x, int y, t_color color) {
    uint32_t rgb_color = color_to_rgb(color.r, color.g, color.b);
    mlx_put_pixel_to_img(mlx, x, y, rgb_color);
}

// fonction pour clean la mlx.
void mlx_cleanup(t_mlx *mlx)
{
    if (mlx->img)
        mlx_destroy_image(mlx->ptr, mlx->img);
    if (mlx->win)
        mlx_destroy_window(mlx->ptr, mlx->win);
    if (mlx->ptr)
        free(mlx->ptr);
    free(mlx);
}

void draw_render_to_img(t_world *world, t_mlx *mlx)
{
    mlx_hook(mlx->win, 17, 0L, mlx_event_close_win, mlx);
    mlx_loop_hook(mlx->ptr, refresh_display, world);
    mlx_loop(mlx->ptr);
}

int refresh_display(t_world *world) 
{
    mlx_put_image_to_window(world->mlx->ptr, world->mlx->win, world->mlx->img, 0, 0);
    return 0;
}