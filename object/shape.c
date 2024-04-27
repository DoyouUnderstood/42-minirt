#include "test_shape.h"
#include "../include/shape.h"
#include <stdlib.h>
#include "../graphics/graphics.h"

// fonction intersect generalise
t_intersection* intersect_shape(t_object *object, t_ray *ray, int *count) 
{
    *count = 0;
    t_matrix inverse_transform = matrix_inverse(object->shape->transformation);
    t_ray local_ray = ray_transform(inverse_transform, *ray);
    return (object->shape->local_intersect(object, &local_ray, count));
}


// Fonction normal_at généralisée
t_tuple normal_at_shape(t_object *obj, t_tuple world_point)
{
    t_tuple local_point = matrix_multiply_by_tuple(matrix_inverse(obj->shape->transformation), world_point);
    t_tuple local_normal = obj->shape->local_normal_at(obj->shape, local_point);
    t_matrix trans_inv = matrix_transpose(matrix_inverse(obj->shape->transformation));
    t_tuple world_normal = matrix_multiply_by_tuple(trans_inv, local_normal);
    world_normal.w = 0;
    return vector_normalize(world_normal);  
}

//fonction pour cree une intersection
t_intersection intersection_create(double t, t_object *obj) 
{
    t_intersection i;
    i.t = t;
    i.obj = obj;
    return i;
}

// Fonction pour identifier le hit parmi une collection d'intersections
t_intersection* hit(t_intersection* intersections, int count) 
{
    t_intersection* hit = NULL;
    double min_t = DBL_MAX;

    for (int i = 0; i < count; i++) {
        if (intersections[i].t > 0 && intersections[i].t < min_t) {
            hit = &intersections[i];
            min_t = intersections[i].t;
        }
    }
    return (hit);
}

t_color calculate_color(t_intersection *closest_hit, t_ray *ray, t_light *light) {
    if (closest_hit != NULL) {
        t_tuple hit_point = t_point_position(ray, closest_hit->t);
        t_tuple normal = closest_hit->obj->shape->local_normal_at(closest_hit->obj->shape, hit_point);
        t_tuple eye = vector_negate(ray->direction);
        return lighting(closest_hit->obj->shape->material, closest_hit->obj, light, &hit_point, &eye, &normal, false);
    } else {
        return (t_color){0, 0, 0};
    }
}
