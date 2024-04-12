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
        mlx_cleanup(mlx);
        exit(0);
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

int mouse_press(int button, int x, int y, void *param)
{
    t_world *world = (t_world*)param;
    (void)x;
    (void)y;
    if (button == 1)
    {
        world->light->intensity.b -= 0.1;
        write(1, "toucheyy", 8);
    }
    return (1);
}