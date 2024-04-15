#include "include/main.h"
#include <math.h>
#include "object/test_shape.h"
void error_exit(char *error_msg)
{
    printf("%s\n", error_msg);
    exit(1);
}


void unit_test()
{   
    struct criterion_test_set *tests = criterion_initialize();
    int result = criterion_run_all_tests(tests);
    criterion_finalize(tests);
    (void)result;
    error_exit("TEST FONCTION");
}

int key_press(int key, void *param);

int refresh_display(t_world *world) 
{
    mlx_put_image_to_window(world->mlx->ptr, world->mlx->win, world->mlx->img, 0, 0);
    int win_width = 1200;
    int pos_x = win_width - world->mlx->width;
    mlx_put_image_to_window(world->mlx->ptr, world->mlx->win, world->mlx->menu, pos_x, 0);
    return 0;
}

void draw_render_to_img(t_world *world, t_mlx *mlx)
{
    mlx_hook(mlx->win, 17, 0L, mlx_event_close_win, mlx);
    mlx_mouse_hook(mlx->win, mouse_press, world);
    mlx_key_hook(mlx->win, key_press, world);

    mlx_loop_hook(mlx->ptr, refresh_display, world);
    mlx_loop(mlx->ptr);
}



#define UNIT_TEST 0

int main(int argc, char *argv[]) 
{
    (void)argc;
    (void)argv;

    if (UNIT_TEST == 1) {
        unit_test();
        return 0;
    }

    t_world *world = NULL;
    t_mlx *mlx = NULL;
    t_camera *camera = NULL;

    world_init(&world, &camera);
    mlx_initialisation(&mlx);   

    if (!mlx) {
        fprintf(stderr, "Failed to initialize MLX\n");
        return 1;
    }

    world->camera = camera;
    world->mlx = mlx;

    render(world);

    return 0;
}
