#include "../include/main.h"

#include "../include/graphics.h"
#include "../include/mathematique.h"
#include "../include/shape.h"


#define MAZ_OBJECTS 10

void world_add_object(t_world* world, t_object* object) {
    if (world->object_count < MAX_OBJECTS) {
        world->objects[world->object_count++] = object;
    } else {
        error_exit("le monde a atteint son maximum faut enlever des objects l'ami");
    }
}

t_world* world_create() {
    t_world* w = malloc(sizeof(t_world));
    if (!w) 
        return NULL;
    
    w->light = NULL;
    w->object_count = 0;
    w->objects = malloc(MAX_OBJECTS * sizeof(t_object*));
    if (!w->objects) {
        free(w);
        return NULL;
    }
    for (int i = 0; i < MAX_OBJECTS; i++) {
        w->objects[i] = NULL;
    }
    return w;
}


void world_destroy(t_world* world) {
    if (!world) 
        return;
    for (int i = 0; i < world->object_count; i++) {
        free(world->objects[i]);
    }
    free(world->objects);
    free(world);
}

// Define the default world
t_world* world_default() {
    t_world* w = world_create();
    if (!w) 
        return NULL;

    t_tuple light_position = point_create(-10, 10, -10);
    t_color light_color = {1, 1, 1};
    t_light* light = light_create(light_color, light_position);
    w->light = light;
    t_sphere* s1 = sphere_create();
    t_object* obj1;
    obj1 = object_create_for_sphere(s1);
    world_add_object(w, obj1);
    t_sphere* s2 = sphere_create();
    t_object* obj2;
    obj2 = object_create_for_sphere(s2);
    obj2->shape->transformation = matrix_scaling(0.5, 0.5, 0.5);
    world_add_object(w, obj2);
    w->object_count = 2;
    return w;
}
