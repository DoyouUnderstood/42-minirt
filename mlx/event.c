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

// static int is_shape_selected = 0;

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
            return stripe_pattern_create(color1, color2);
    }
}


static t_shape *selected_shape = NULL;

bool is_selected(t_shape *shape) {
    return (shape && shape->material.ambient == 0.7);
}

void make_it_shine(t_shape *shape) {
    if (shape) {
        shape->material.ambient = 0.7;
    }
}

void make_it_normal(t_shape *shape) {
    if (shape) {
        shape->material.ambient = 0.1;
    }
}

static int current_pattern = 0; // Déplacé en variable globale ou statique si ce n'est pas déjà le cas

void handle_pattern_change(t_shape *selected_shape) {
    selected_shape->material.pattern = change_pattern(current_pattern, (t_color){0.4, 0.4, 0.5}, (t_color){0.6, 0.4, 0.5});
    current_pattern = (current_pattern + 1) % 5;
}

void handle_shape_selection(t_world *world, int x, int y) {
    t_matrix inverse_transform = matrix_inverse(world->camera->transform);
    t_ray ray = ray_for_pixel(world->camera, &inverse_transform, x, y);
    int count;
    t_intersection *intersections = intersect_world(world, &ray, &count);
    if (count > 0) {
        t_shape *clicked_shape = intersections[0].obj->shape;
        if (selected_shape == clicked_shape) {
            make_it_normal(selected_shape);
            selected_shape = NULL;
        } else {
            if (selected_shape) make_it_normal(selected_shape);
            selected_shape = clicked_shape;
            make_it_shine(selected_shape);
        }
    } else {
        if (selected_shape) {
            make_it_normal(selected_shape);
            selected_shape = NULL;
        }
    }
    free(intersections);
}


void handle_color_change(t_shape *shape)
{
    if (shape->material.pattern.color_a.r < 1)
        shape->material.pattern.color_a.r += 0.1;
    else
        write(1, "RED IS AT MAX CHILL OUT\n", 24);
}

void handle_green_increase(t_shape *shape) {
    if (shape->material.pattern.color_a.g < 1)
        shape->material.pattern.color_a.g += 0.1;
    else
        write(1, "GREEN IS AT MAX\n", 17);
}

void handle_green_decrease(t_shape *shape) {
    if (shape->material.pattern.color_a.g > 0)
        shape->material.pattern.color_a.g -= 0.1;
    else
        write(1, "GREEN IS AT MIN\n", 17);
}

int mouse_press(int button, int x, int y, void *param) {
    t_world *world = (t_world*)param;
    printf("voici les coord : x : %d et y : %d\n", x , y);
    if (button == 1) {
        if (x > 950 && x < 1030 && y > 206 && y < 224 && selected_shape)
                handle_pattern_change(selected_shape);
        else if (x > 1018 && x < 1061 && y > 234 && y < 251 && selected_shape)
                handle_color_change(selected_shape);
        else if (x > 1071 && x < 1090 && y > 233 && y < 250 && selected_shape) {
            handle_green_increase(selected_shape);
        } else if (x > 1099 && x < 1112 && y > 235 && y < 248 && selected_shape) {
            handle_green_decrease(selected_shape);
        } 
        else {
            handle_shape_selection(world, x, y);
        }
        render(world);
    }
    return 1;
}




int key_press(int key, void *param) {
    t_world *world = (t_world*)param;
    static int selected_object_index = 0;

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

