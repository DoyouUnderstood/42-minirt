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

void draw_render_to_img(t_world *world, t_mlx *mlx)
{
    mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
    mlx_hook(mlx->win, 17, 0L, mlx_event_close_win, mlx);
    mlx_mouse_hook(mlx->win, mouse_press, world);
    mlx_key_hook(mlx->win, key_press, world);

    mlx_loop(mlx->ptr);
    mlx_destroy_window(mlx->ptr, mlx->win);
}

#define UNIT_TEST 0

int main(int argc, char *argv[]) 
{
    (void)argc;
    (void)argv;
    t_mlx *mlx = NULL; 
    t_world *world = NULL;
    t_camera *camera = NULL;

    if (UNIT_TEST == 1) {
        unit_test();
    } else {
        world_init(&world, &camera);
        mlx_initialisation(&mlx);
        world->camera = camera;
        world->mlx = mlx;
        render(world);
        draw_render_to_img(world, mlx);
       
    }
    return (0);
}
