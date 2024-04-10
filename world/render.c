#include "../include/main.h"

#include "../include/graphics.h"
#include "../include/mathematique.h"
#include "../include/shape.h"
#include <math.h>

// convertir for en while pour la norme. 
void render(t_mlx *mlx, t_world *world, t_camera *camera) 
{
    int x;
    int y;

    x = 0;
    y = 0;
    t_matrix inverse_transform = matrix_inverse(camera->transform);
    while (y < camera->vsize)
    {
        x = 0;
        while(x < camera->hsize) 
        {
            t_ray ray = ray_for_pixel(camera, &inverse_transform, x, y);
            t_color color = color_at(world, &ray);
            draw_pixel(mlx, x, y, color);
            x++;
        }
        y++;

    }
    mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
}
