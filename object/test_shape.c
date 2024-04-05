#include "test_shape.h"

t_matrix *transformation_default(t_test_shape *shape)
{
    shape->transformation = matrix_init_identity();
    return (shape);
}