#include "../include/init.h"
#include "../object/test_shape.h"

// Initialisation de world. 
void world_init(t_world **world, t_camera **camera) 
{
    *world = world_create();
    *camera = camera_create(820, 620, M_PI / 3);
    (*camera)->transform = view_transform(point_create(-1, 1.5, -5), point_create(0, 1, 0), vector_create(0, 1, 0));
    world_fill(*world);
}

// Initialisation de MLX.
void mlx_initialisation(t_mlx **mlx) {
    *mlx = mlx_init_and_create_window(820, 620, "minirt");
    if (!(*mlx))
        error_exit("Erreur initialisation mlx\n");
    mlx_create_image(*mlx);
}


void add_spheres(t_world *world) {
    // 1ère sphère au milieu
    t_sphere *middle = create_sphere();
    t_object *obj_middle = object_create_for_sphere(middle);
    obj_middle->shape->transformation = matrix_multiply(matrix_translation(-0.5, 0.5, 0.5), matrix_scaling(0.5, 0.5, 0.5));
    obj_middle->shape->material.color = (t_color){0.1, 1, 0.5};
    world_add_object(world, obj_middle);

    // 2ème sphère à droite
    t_sphere *right = create_sphere();
    t_object *obj_right = object_create_for_sphere(right);
    obj_right->shape->transformation = matrix_multiply(matrix_translation(1.5, 0.25, -0.5), matrix_scaling(0.25, 0.25, 0.25));
    obj_right->shape->material.color = (t_color){1, 0.1, 1};
    world_add_object(world, obj_right);

    // 3ème sphère à gauche
    t_sphere *left = create_sphere();
    t_object *obj_left = object_create_for_sphere(left);
    obj_left->shape->transformation = matrix_multiply(matrix_translation(-1, 0.33, -1.75), matrix_scaling(0.33, 0.33, 0.33));
    obj_left->shape->material.color = (t_color){1, 0.8, 0.1};
    world_add_object(world, obj_left);
}


void world_fill(t_world *world) {
    // Création du sol
    t_plane *floor = plane_create();
    t_object *obj_floor = object_create_for_plane(floor);
    world_add_object(world, obj_floor);

    // Création du mur de fond
    t_plane *back_wall = plane_create();
    t_object *obj_back_wall = object_create_for_plane(back_wall);
    obj_back_wall->shape->transformation = matrix_multiply(
        matrix_translation(0, 0, 5),  // Translater le mur vers l'arrière
        matrix_rotation_x(M_PI / 2)   // Rotater le mur pour le rendre vertical
    );
    world_add_object(world, obj_back_wall);

    // Création du mur de droite
    t_plane *right_wall = plane_create();
    t_object *obj_right_wall = object_create_for_plane(right_wall);
    obj_right_wall->shape->transformation = matrix_multiply(
        matrix_translation(5, 0, 0),  // Déplace le mur vers la droite de la scène
        matrix_rotation_y(-M_PI / 2)  // Rotater le mur pour l'aligner avec l'axe y
    );
    world_add_object(world, obj_right_wall);

    // Création du mur de gauche
    t_plane *left_wall = plane_create();
    t_object *obj_left_wall = object_create_for_plane(left_wall);
    obj_left_wall->shape->transformation = matrix_multiply(
        matrix_translation(-5, 0, 0), // Translater le mur vers la gauche
        matrix_rotation_y(M_PI / 2)   // Rotater le mur pour l'aligner avec l'axe y
    );
    world_add_object(world, obj_left_wall);

    // Ajout des sphères partiellement encastrées dans le sol
    add_spheres(world);

    // Ajout de la lumière
    world->light = light_create((t_color){1, 1, 1}, point_create(-10, 10, -10));
}

