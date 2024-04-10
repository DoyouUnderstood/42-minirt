#include "include/shape.h"
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

void    world_fill(t_world *world)
{
    // 1er sphere
    t_sphere *floor = create_sphere();
    t_object *obj_floor = object_create_for_sphere(floor);
    obj_floor->shape->transformation = matrix_scaling(10,0.01,10);
    obj_floor->shape->material.color = (t_color){1 , 0.9, 0.9};
    obj_floor->shape->material.specular = 0;
    world_add_object(world, obj_floor);

    // 2eme sphere
    t_sphere *left_wall = create_sphere();
    t_object *obj_leftw = object_create_for_sphere(left_wall);
    obj_leftw->shape->transformation = matrix_multiply(
        matrix_translation(0, 0, 5),
        matrix_multiply(
            matrix_rotation_y(-M_PI_4),
            matrix_multiply(
                matrix_rotation_x(M_PI / 2),
                matrix_scaling(10, 0.01, 10)
            )
        )
    );
    obj_leftw->shape->material = obj_floor->shape->material;
    world_add_object(world, obj_leftw);

    //3eme sphere
    t_sphere *right_w = create_sphere();
    t_object *obj_rightw = object_create_for_sphere(right_w);
    obj_rightw->shape->transformation = matrix_multiply(
        matrix_translation(0, 0, 5),
        matrix_multiply(
            matrix_rotation_y(M_PI_4),
            matrix_multiply(
                matrix_rotation_x(M_PI / 2),
                matrix_scaling(10, 0.01, 10)
            )
        )
    );
    obj_rightw->shape->material = obj_floor->shape->material;

    world_add_object(world, obj_rightw);

    // 4eme sphere 
    t_sphere* middle = create_sphere();
    t_object *obj_middle = object_create_for_sphere(middle);
    obj_middle->shape->transformation = matrix_translation(-0.5, 1, 0.5);
    obj_middle->shape->material.color = (t_color){0.1, 1, 0.5};
    obj_middle->shape->material.specular = 0.3;
    obj_middle->shape->material.diffuse = 0.7;
    world_add_object(world, obj_middle);
    //5eme sphere

    t_sphere *right = create_sphere();
    t_object *obj_r = object_create_for_sphere(right);
    obj_r->shape->transformation = matrix_multiply(matrix_translation(1.5, 0.5, -0.5), matrix_scaling(0.5, 0.5, 0.5));
    obj_r->shape->material.color = (t_color){0.5, 1, 0.1};
    obj_r->shape->material.diffuse = 0.7;
    obj_r->shape->material.diffuse = 0.3;

    world_add_object(world, obj_r);

    // 6e sphere 
    t_sphere *left = create_sphere();
    t_object *obj_left = object_create_for_sphere(left);
    obj_left->shape->transformation = matrix_multiply(matrix_translation(-1.5, 0.33, -1.75), matrix_scaling(0.33, 0.33, 0.33));
    obj_left->shape->material.color = (t_color){1, 0.8, 0.1};
    obj_left->shape->material.diffuse = 0.7;
    obj_left->shape->material.specular = 0.3;
    world_add_object(world, obj_left);

    world->light = light_create((t_color){1, 1, 1}, point_create(-10, 10, -10));

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


void    mlx_initialisation(void)
{
    t_mlx *mlx = mlx_init_and_create_window(820, 620, "minirt");
    if (!mlx) 
        error_exit("erreur initialisation mlx\n");
    mlx_create_image(mlx);
    t_world *world = world_create();
    t_camera camera = camera_create(820, 620, M_PI / 3);
    camera.transform = view_transform(point_create(-1, 1.5, -5), point_create(0, 1, 0), vector_create(0, 1, 0));

    world_fill(world);
    render(mlx, world, &camera);

    mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
    mlx_hook(mlx->win, 17, 0L, mlx_event_close_win, mlx);
    mlx_mouse_hook(mlx->win, mouse_press, world);
    mlx_loop(mlx->ptr);
    mlx_destroy_window(mlx->ptr, mlx->win);
}

#define UNIT_TEST 0

int main(int argc, char *argv[]) 
{
    (void)argc;
    (void)argv;
    if (UNIT_TEST == 1)
        unit_test();
    else
    {
        mlx_initialisation();
    }
    
    return (0);
}