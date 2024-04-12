#ifndef MINILIBX_H
#define MINILIBX_H


#include "main.h"
#include "../lib/mlx/mlx.h"
#include "graphics.h"
// #define KEY_ESC 0xff1b
// #define KEY_RIGHT 0xff53
// #define KEY_LEFT 0xff51
// #define KEY_UP 0xff52
// #define KEY_DOWN 0xff54
// #define KEY_SHRINK_ROTATE 'q' // s
// #define KEY_SHRINK_SHEAR 'w'  // d
// #define KEY_A 'a'
// #define KEY_S 's'
// #define KEY_D 'd'
// #define KEY_F 'f'
// #define KEY_G 'g'
// #define KEY_H 'h'
// #define KEY_J 'j'
// #define KEY_K 'k'

typedef struct s_color t_color;

typedef struct s_mlx
{
    void    *ptr;
    void    *win;
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     width;
    int     height;
}               t_mlx;

// ============= FONCTION MLX ================

void    mlx_put_pixel_to_img(t_mlx *mlx, int x, int y, int color);
int     mlx_create_image(t_mlx *mlx);
t_mlx   *mlx_init_and_create_window(int width, int height, char *title);
void    mlx_cleanup(t_mlx *mlx);
int     mlx_event_close_win(t_mlx *mlx);
int     mlx_event_handle_key(int keycode, void *param);
void    draw_pixel(t_mlx *mlx, int x, int y, t_color color);
int     mouse_press(int button, int x, int y, void *param);

#endif

