#include "test_shape.h"

t_sphere* create_sphere() 
{
    t_sphere* sphere = malloc(sizeof(t_sphere));
    if (!sphere) return NULL;

    sphere->center = point_create(0, 0, 0);
    sphere->diameter = 1;

    return (sphere);
}
