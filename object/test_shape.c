#include "test_shape.h"
#include "../include/shape.h"


#include <stdlib.h>

// t_shape *test_shape(void) 
// {
//     t_shape *shape = malloc(sizeof(t_shape));
//     if (!shape) 
//         return NULL;

//     shape->transformation = matrix_init_identity();
//     shape->material = material_create_default();

//     shape->local_intersect = local_intersect;
//     shape->local_normal_at = test_local_normal_at;

//     return (shape);
// }


t_intersection* test_local_intersect(t_shape *shape, t_ray *local_ray, int *count) {
    shape->saved_ray = *local_ray;
    *count = 0;
    return NULL;
}

t_tuple test_local_normal_at(t_shape *shape, t_tuple local_point) {
    (void)shape; // Marquer object comme inutilisé
    (void)local_point; // Marquer local_point comme inutilisé
    return (t_tuple){.x = 0.0, .y = 1.0, .z = 0.0, .w = 0.0};
}
t_tuple local_normal_at_sphere(t_shape *shape, t_tuple local_point) 
{
    (void)shape; // Marque le paramètre comme explicitement inutilisé
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

/*
function​ intersect(shape, ray)
​ 	  local_ray ← transform(ray, inverse(shape.transform))
​ 	  ​return​ local_intersect(shape, local_ray)
​ 	​end​ ​function​*/




// t_intersection* local_intersect(t_shape *shape, t_ray *ray, int *count) 
// {
//     shape->saved_ray = *ray; // Assignation directe puisque ray est de type t_ray
//     *count = 0;
//     return NULL;
// }

t_intersection* intersect_shape(t_object *object, t_ray *ray, int *count) 
{
    *count = 0;
    // printf("object : %d\n", object->obj->shape->material.color);
    t_matrix inverse_transform = matrix_inverse(object->shape->transformation);
    t_ray local_ray = ray_transform(inverse_transform, *ray);
    return (object->shape->local_intersect(object, &local_ray, count));
}


// Fonction normal_at généralisée
t_tuple normal_at_shape(t_object *obj, t_tuple world_point) {
    // Convertit le point du monde à l'espace local de l'objet
    t_tuple local_point = matrix_multiply_by_tuple(matrix_inverse(obj->shape->transformation), world_point);
    // Calcule la normale en espace local

    t_tuple local_normal = obj->shape->local_normal_at(obj->shape, local_point);
    // Convertit la normale de l'espace local au monde
    t_matrix trans_inv = matrix_transpose(matrix_inverse(obj->shape->transformation));
    t_tuple world_normal = matrix_multiply_by_tuple(trans_inv, local_normal);
    world_normal.w = 0; // Assurez-vous que c'est un vecteur
    return vector_normalize(world_normal); // Normalise le vecteur
}
