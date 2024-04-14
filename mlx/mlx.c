#include "../include/minilibx.h"

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

// fonction pour cree une image.
int mlx_create_image(t_mlx *mlx)
{
    mlx->img = mlx_new_image(mlx->ptr, mlx->width, mlx->height);
    if (!mlx->img)
        error_exit("erreur creation image\nmlx.c l34\n");
    mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
                                  &mlx->line_length, &mlx->endian);
    return (1);
}

// fonction pour ajouter un pixel dans l'image
void mlx_put_pixel_to_img(t_mlx *mlx, int x, int y, int color) 
{
    if (!mlx || !mlx->addr)
        error_exit("erreur put pixel to img mlx.c\n");
    int pixel_index = (y * mlx->line_length) + (x * (mlx->bits_per_pixel / 8));
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