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
#define KEY_R 'r'
#define KEY_G 'g'
#define KEY_B 'b'


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

#define KEY_H 'h'
#define KEY_R 'r'
#define KEY_G 'g'
#define KEY_B 'b'


#include "../object/test_shape.h"

t_pattern change_pattern(int pattern_type, t_color color1, t_color color2) {
    switch (pattern_type) {
        case 1:
            return ring_pattern_create(color1, color2);
        case 2:
            return stripe_pattern_create(color1, color2);
        case 3:
            return checker_pattern_create(color1, color2);
        case 4:
            return gradient_pattern_create(color1, color2);
        default:
            return stripe_pattern_create(color1, color2); // Retourne un motif par défaut
    }
}


int mouse_press(int button, int x, int y, void *param) {
    static int current_pattern = 0;
    t_world *world = (t_world*)param;

    if (button == 1) {
        current_pattern = (current_pattern + 1) % 5; // Cycle through 5 patterns
        t_matrix inverse_transform = matrix_inverse(world->camera->transform);
        t_ray ray = ray_for_pixel(world->camera, &inverse_transform, x, y);
        int count;
        t_intersection *intersections = intersect_world(world, &ray, &count);

        if (count > 0) {
            t_color color1 = {0.2, 0.2, 0.3};
            t_color color2 = {0.2, 0.2, 0.5};
            intersections[0].obj->shape->material.pattern = change_pattern(current_pattern, color1, color2);
            render(world); // Rafraîchissement de la scène
        }

        free(intersections);
    }
    return 1;
}

int key_press(int key, void *param) {
    t_world *world = (t_world*)param;
    static int selected_object_index = 0;  // Index de l'objet actuellement sélectionné

    if (key == KEY_RIGHT) {
        selected_object_index = (selected_object_index + 1) % world->object_count;
    }
    if (key == KEY_LEFT) {
        selected_object_index = (selected_object_index - 1 + world->object_count) % world->object_count;
    }

    t_color *color = &world->objects[selected_object_index]->shape->material.color;

    switch (key) {
        case KEY_R:
            world->objects[selected_object_index]->shape->material.pattern.color_b.r = fmod(color->r + 0.1, 1.0);
            break;
        case KEY_G:
            world->objects[selected_object_index]->shape->material.pattern.color_b.g = fmod(color->g + 0.1, 1.0);
            break;
        case KEY_B:
            world->objects[selected_object_index]->shape->material.pattern.color_b.b = fmod(color->b + 0.1, 1.0);
            break;
    }

    render(world);
    return 0;
}

