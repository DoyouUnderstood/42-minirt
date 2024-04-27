#include "../include/main.h"
#include "../include/mathematique.h"
#include "../include/shape.h"
#include "../object/test_shape.h"



#define MAX_OBJECTS 10

// add object into world.
void world_add_object(t_world* world, t_object* object) 
{
    if (object == NULL)
        return ;
    if (world->object_count < MAX_OBJECTS) {
        world->objects[world->object_count++] = object;
    } else {
        error_exit("le monde a atteint son maximum faut enlever des objects l'ami");
    }
}

// initialisation of world.
t_world* world_create() 
{
    t_world* w = malloc(sizeof(t_world));
    if (!w) 
        return NULL;
    
    w->light = NULL;
    w->camera = NULL;
    w->object_count = 0;
    w->objects = malloc(MAX_OBJECTS * sizeof(t_object*));
    if (!w->objects) {
        free(w);
        return NULL;
    }
    for (int i = 0; i < MAX_OBJECTS; i++)
        w->objects[i] = NULL;
    return w;
}

// annihilation of world.
void world_destroy(t_world* world) {
    if (!world) 
        return;
    for (int i = 0; i < world->object_count; i++) {
        free(world->objects[i]);
    }
    free(world->objects);
    free(world);
}
