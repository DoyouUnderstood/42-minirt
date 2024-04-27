#include "test_shape.h"
#include "../include/shape.h"
#include "../object/test_shape.h"
#include "../graphics/graphics.h"

t_material *material_create_default_plane(t_color *color);

// Cree un nouvel object t_object pour un plane. 
t_object* object_create_for_plane(t_color color, t_tuple center)
{
    t_plane *plane = plane_create(center);
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
    obj->shape->material = material_create_default_plane(&color);
    obj->shape->local_normal_at = plane_local_normal_at;
    obj->shape->local_intersect = plane_local_intersect;
    t_matrix translation = matrix_translation(center.x, center.y, center.z);
    t_matrix scaling = matrix_scaling(1, 1, 1);
    obj->shape->transformation = matrix_multiply(translation, scaling);
    plane->center = (t_tuple){0,0,0,0};
    return obj;
}

t_plane *plane_create(t_tuple center)
{
    t_plane *plane = malloc(sizeof(t_plane));
    plane->center = center;
    return (plane);
}

t_tuple plane_local_normal_at(t_shape *shape, t_tuple local_point) 
{
    (void)local_point;
    (void)shape;
    return vector_create(0, 1, 0);
}


t_intersection* plane_local_intersect(t_object *obj, t_ray *ray, int *count) {
    if (fabs(ray->direction.y) < TUPLE_EPSILON) {
        *count = 0;
        return NULL;
    }

    double t = -ray->origin.y / ray->direction.y;
    
    *count = 1;
    t_intersection *intersections = (t_intersection *)malloc(sizeof(t_intersection));
    if (!intersections) {
        *count = 0;
        return NULL;
    }
    intersections[0] = (t_intersection){t, obj};

    return intersections;
}
