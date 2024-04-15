#include "../include/init.h"
#include "../object/test_shape.h"

// Initialisation de world. 
void world_init(t_world **world, t_camera **camera) 
{
    *world = world_create();
    *camera = camera_create(1200, 920, M_PI / 6);
    (*camera)->transform = view_transform(point_create(-3, 1.5, -7), point_create(0, 1, 0), vector_create(0, 1, 0));
    world_fill(*world);
}

// Initialisation de MLX.
void mlx_initialisation(t_mlx **mlx) {
    *mlx = mlx_init_and_create_window(1200, 920, "minirt");
    if (!(*mlx))
        error_exit("Erreur initialisation mlx\n");

    mlx_create_image(*mlx);

    int width, height;

    (*mlx)->menu = mlx_xpm_file_to_image((*mlx)->ptr, "menu.xpm", &width, &height);

    if (!(*mlx)->menu) {
        error_exit("Erreur de chargement de menu.xpm\n");
    }

    (*mlx)->width = width;
    (*mlx)->height = height;
}


void add_spheres(t_world *world) 
{
    // 1ère sphère au milieu
    t_sphere *middle = create_sphere();
    t_object *obj_middle = object_create_for_sphere(middle);
    obj_middle->shape->transformation = matrix_multiply(matrix_translation(-0.5, 0.5, -0.5), matrix_scaling(0.5, 0.5, 0.5));
    obj_middle->shape->material.color = (t_color){0.1, 1, 0.5};
    world_add_object(world, obj_middle);

    // 2ème sphère à droite
    t_sphere *right = create_sphere();
    t_object *obj_right = object_create_for_sphere(right);
    obj_right->shape->transformation = matrix_multiply(matrix_translation(1.5, 0.25, -0.5), matrix_scaling(0.25, 0.25, 0.25));
    obj_right->shape->material.color = (t_color){1, 1, 1};
    world_add_object(world, obj_right);

    // // 2ème sphère à droite
    // t_sphere *right2 = create_sphere();
    // t_object *obj_right2 = object_create_for_sphere(right2);
    // obj_right2->shape->transformation = matrix_multiply(matrix_translation(10.5, 3.25, 35.5), matrix_scaling(3.25, 3.25, 3.25));
    // obj_right2->shape->material.color = (t_color){1, 1, 1};
    // world_add_object(world, obj_right2);

    // 3ème sphère à gauche
    t_sphere *left = create_sphere();
    t_object *obj_left = object_create_for_sphere(left);
    obj_left->shape->transformation = matrix_multiply(matrix_translation(-1, 0.33, -1.75), matrix_scaling(0.33, 0.33, 0.33));
    // obj_left->shape->material.color = (t_color){1, 0.8, 0.1};
    world_add_object(world, obj_left);
}


void world_fill(t_world *world) {
    // Création du sol
    t_plane *floor = plane_create();
    t_object *obj_floor = object_create_for_plane(floor);
    world_add_object(world, obj_floor);

    t_plane *back_wall = plane_create();
    t_object *obj_back_wall = object_create_for_plane(back_wall);
    obj_back_wall->shape->transformation = matrix_multiply(matrix_translation(0, 0, 5), matrix_rotation_x(M_PI / 2));
    world_add_object(world, obj_back_wall);

    // Ajout des sphères partiellement encastrées dans le sol
    add_spheres(world);

    // Ajout de la lumière
    world->light = light_create((t_color){1, 1, 1}, point_create(-10, 10, -10));
}

