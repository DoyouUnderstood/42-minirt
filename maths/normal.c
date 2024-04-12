#include "../include/shape.h"
#include "../include/mathematique.h"
#include "../object/test_shape.h"

typedef struct s_sphere t_sphere;
t_tuple 	matrix_multiply_by_tuple(t_matrix mat, t_tuple tup);


// Calcule la normale à un point donné sur la surface de la sphère.
t_tuple normal_at(t_object *obj, t_tuple world_point) 
{
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
