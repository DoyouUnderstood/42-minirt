#include "../include/shape.h"
#include "../include/mathematique.h"

typedef struct s_sphere t_sphere;
t_tuple 	matrix_multiply_by_tuple(t_matrix mat, t_tuple tup);


// Calcule la normale à un point donné sur la surface de la sphère.
t_tuple normal_at(const t_sphere* sphere, t_tuple world_point) 
{
    t_matrix inverse_transform = matrix_inverse(sphere->transform);
    t_tuple object_point = matrix_multiply_by_tuple(inverse_transform, world_point);
    t_tuple object_normal = point_sub(object_point, point_create(0, 0, 0));
    t_tuple world_normal = matrix_multiply_by_tuple(matrix_transpose(inverse_transform), object_normal);
    world_normal.w = 0.0;
    return (vector_normalize(world_normal));
}
