#include "../include/minilibx.h"

#define KEY_ESC 53
#define KEY_RIGHT 124
#define KEY_LEFT 123
#define KEY_UP 126
#define KEY_DOWN 125
#define KEY_SHRINK_ROTATE 'q'// 'q'
#define KEY_SHRINK_SHEAR 'w' // 'w'
#define KEY_A 'a'
#define KEY_S 's'
#define KEY_D 'd'
#define KEY_F 'f'
#define KEY_K 40


//fonction evenement pour quitter avec echap
int mlx_event_handle_keypress(int keysym, t_mlx *mlx)
{
    if (keysym == KEY_ESC)
    {
        mlx_cleanup(mlx); // Nettoie et libère les ressources
        exit(0); // Ferme l'application
    }
    return (0);
}

// fonction pour quitter avec la croix rouge
int mlx_event_close_win(t_mlx *mlx)
{
    mlx_cleanup(mlx);
    exit(0);
    return (0);
}

void apply_transformation_to_sphere(t_sphere *sphere, t_matrix transformation) 
{
    sphere->transform = matrix_multiply(sphere->transform, transformation);
}

// void redraw_scene(t_mlx *mlx, t_matrix transformation) 
// {

//     t_light light;
//     light.pos = point_create(-10 , 10, -10);
//     light.intensity = (t_color){1, 1, 1};

//     if (mlx == NULL || mlx->ptr == NULL) {
//         write(1, "Invalid scene or MLX pointer.\n", 30);
//         return;
//     }
//     if (mlx->img != NULL) 
//     {
//         mlx_destroy_image(mlx->ptr, mlx->img);
//     }
//     mlx->img = mlx_new_image(mlx->ptr, mlx->width, mlx->height);
//     if (mlx->img == NULL) 
//     {
//         write(1, "Failed to create image.\n", 24);
//         return;
//     }
//     mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
//     t_sphere *sphere;
//     sphere = sphere_create();
//     apply_transformation_to_sphere(sphere, transformation);
//     ray_throw(mlx, sphere, &light);
//     mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
// }

// int mlx_event_handle_key(int keycode, void *param) 
// {
//     t_mlx *mlx = (t_mlx*)param;
//     t_matrix transformation = matrix_init_identity();
//     if (keycode == KEY_A) {
//         transformation = matrix_scaling(1, 0.5, 1); // Rétrécir le long de l'axe Y
//     } else if (keycode == KEY_S) {
//         transformation = matrix_scaling(0.5, 1, 1); // Rétrécir le long de l'axe X
//     } else if (keycode == KEY_SHRINK_ROTATE) {
//         t_matrix rotation = matrix_rotation_z(M_PI / 4);
//         t_matrix scaling = matrix_scaling(0.5, 1, 1); // Réduire et faire pivoter
//         transformation = matrix_multiply(rotation, scaling);
//     } else if (keycode == KEY_SHRINK_SHEAR) {
//         t_matrix shearing = matrix_shearing(1, 0, 0, 0, 0, 0);
//         t_matrix scaling = matrix_scaling(0.5, 1, 1); // Rétrécir et incliner
//         transformation = matrix_multiply(shearing, scaling);
//     }
//     redraw_scene(mlx, transformation);
//     return (0);
// }

