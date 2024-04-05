#include "include/shape.h"
#include "include/main.h"
#include <math.h>

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
    t_object *object = malloc(sizeof(t_object));
    t_object *object1 = malloc(sizeof(t_object));
    t_object *object2 = malloc(sizeof(t_object));
    t_object *object3 = malloc(sizeof(t_object));
    t_object *object4 = malloc(sizeof(t_object));

    t_sphere *floor = sphere_create();
    floor->transform = matrix_scaling(10, 0.01, 10);
    floor->material = material_create_default();
    floor->material.color = (t_color){1, 0.9, 0.9};
    floor->material.specular = 0;
    object = object_create_for_sphere(floor);
    world_add_object(world, object);

    t_sphere *left_wall = sphere_create();
    left_wall->transform = matrix_multiply(
        matrix_translation(0, 0, 5),
        matrix_multiply(
            matrix_rotation_y(-M_PI_4),
            matrix_multiply(
                matrix_rotation_x(M_PI / 2),
                matrix_scaling(10, 0.01, 10)
            )
        )
    );
    left_wall->material = floor->material;

    object2 = object_create_for_sphere(left_wall);
    world_add_object(world, object2);
    
    t_sphere *right_wall = sphere_create();
    right_wall->transform = matrix_multiply(
        matrix_translation(0, 0, 5),
        matrix_multiply(
            matrix_rotation_y(M_PI_4),
            matrix_multiply(
                matrix_rotation_x(M_PI / 2),
                matrix_scaling(10, 0.01, 10)
            )
        )
    );
    right_wall->material = floor->material; // Assurez-vous que floor->material a été correctement initialisé avant cette ligne.
    object1 = object_create_for_sphere(right_wall);
    world_add_object(world, object1);



    t_sphere *middle = sphere_create();
    middle->transform = matrix_translation(-0.5, 1, 0.5);
    middle->material = material_create_default();
    middle->material.color = (t_color){0.1, 1, 0.5};
    middle->material.diffuse = 0.7;
    middle->material.specular = 0.3;
    object2 = object_create_for_sphere(middle);
    world_add_object(world, object2);

    t_sphere *right = sphere_create();
    right->transform = matrix_multiply(matrix_translation(1.5, 0.5, -0.5), matrix_scaling(0.5, 0.5, 0.5));
    right->material = material_create_default();
    right->material.color = (t_color){0.5, 1, 0.1};
    right->material.diffuse = 0.7;
    right->material.specular = 0.3;
    object3 = object_create_for_sphere(right);
    world_add_object(world, object3);

    t_sphere *left = sphere_create();
    left->transform = matrix_multiply(matrix_translation(-1.5, 0.5, -0.75), matrix_scaling(0.6, 0.6, 0.6));
    left->material = material_create_default();
    left->material.color = (t_color){1, 0.8, 0.1};
    left->material.diffuse = 0.7;
    left->material.specular = 0.3;
    object4 = object_create_for_sphere(left);
    world_add_object(world, object4);

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
    //mlx_hook(mlx->win, 2, 1L<<0, mlx_event_handle_key, mlx);
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
        mlx_initialisation();
    
    return (0);
}