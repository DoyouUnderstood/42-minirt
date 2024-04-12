#include "test_shape.h"
#include "../include/shape.h"
#include "../object/test_shape.h"
t_plane *plane_create(void)
{
    t_plane *plane = malloc(sizeof(t_plane));
    plane->center = point_create(0, 0, 0);
    plane->color = (t_color){0.3, 0.3, 0.3};
    return (plane);
}

    t_tuple plane_local_normal_at(t_shape *shape, t_tuple local_point) 
    {
        (void)local_point;
        (void)shape;
        return vector_create(0, 1, 0);
    }

    t_intersection* plane_local_intersect(t_object *obj, t_ray *ray, int *count) 
    {
        t_shape *shape = obj->shape;
        t_ray transformed_ray = ray_transform(matrix_inverse(shape->transformation), *ray);
        
        if (fabs(transformed_ray.direction.y) < TUPLE_EPSILON) {
            *count = 0;
            return NULL;
        }

        double t = -transformed_ray.origin.y / transformed_ray.direction.y;
        
        *count = 1;
        t_intersection *intersections = (t_intersection *)malloc(sizeof(t_intersection));
        if (!intersections) {
            *count = 0;
            return NULL;
        }
        intersections[0] = (t_intersection){t, obj};

        return intersections;
    }
