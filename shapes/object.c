#include "../include/shape.h"
#define EPSILON 0.001
#include "../object/test_shape.h"

// Crée un nouvel objet t_object pour une sphère
t_object* object_create_for_sphere(t_sphere* sphere) 
{
    t_object* obj = malloc(sizeof(t_object));
    if (obj == NULL) {
        error_exit("Failed to allocate memory for t_object");
    }
    obj->shape = malloc(sizeof(t_shape));
    obj->type = SPHERE;
    obj->obj = sphere;
    obj->shape->transformation = matrix_init_identity();
    obj->shape->material = material_create_default();
    // t_pattern pattern = stripe_pattern_create(color_create(0.55, 1, 1), color_create(1, 1, 1));
    // obj->shape->material.pattern = pattern;
    obj->shape->local_intersect = local_intersect_sphere;
    obj->shape->local_normal_at = local_normal_at_sphere;

    return obj;
}





// Cree un nouvel object t_object pour un plane. 
t_object* object_create_for_plane(t_plane *plane) {
    t_object *obj = (t_object *)malloc(sizeof(t_object));
    if (!obj) 
        return NULL;

    obj->type = PLANE;
    obj->obj = plane;

    obj->shape = (t_shape *)malloc(sizeof(t_shape));
    if (!obj->shape) {
        free(obj);
        return NULL;
    }
    obj->shape->transformation = matrix_init_identity();
    obj->shape->material = material_create_default_plane();
    obj->shape->local_normal_at = plane_local_normal_at;
    obj->shape->local_intersect = plane_local_intersect;

    return obj;
}
