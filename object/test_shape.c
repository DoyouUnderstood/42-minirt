#include "test_shape.h"
#include "../include/shape.h"
#include <stdlib.h>

t_intersection* test_local_intersect(t_shape *shape, t_ray *local_ray, int *count) {
    shape->saved_ray = *local_ray;
    *count = 0;
    return NULL;
}

t_tuple test_local_normal_at(t_shape *shape, t_tuple local_point) {
    (void)shape;
    (void)local_point;
    return (t_tuple){.x = 0.0, .y = 1.0, .z = 0.0, .w = 0.0};
}
t_tuple local_normal_at_sphere(t_shape *shape, t_tuple local_point) 
{
    (void)shape;
    t_tuple tupl = tuple_subtract(local_point, point_create(0, 0, 0));
    return tupl;
}

void    transformation_default(t_shape *shape)
{
    shape->transformation = matrix_init_identity();
}

void set_shape_transform(t_shape *shape, t_matrix transformation) 
{
    shape->transformation = transformation;
}


void shape_default_material(t_shape *shape)
{
    if (shape != NULL) {
        shape->material = material_create_default();
    }
}

void shape_set_material(t_shape *shape, t_material material)
{
    if (shape != NULL) {
        shape->material = material;
    }
}

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
