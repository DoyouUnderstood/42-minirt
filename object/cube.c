#include "test_shape.h"
#include "../include/shape.h"
#include "../object/test_shape.h"
#include "../graphics/graphics.h"

#include <math.h>
#include <float.h>
#include <stdlib.h>

static t_intersection* cube_intersect(t_object *obj, t_ray *ray, int *count);

// Fonction pour créer un cube encapsulé dans un t_object

t_object* create_cube(t_tuple center, double edge_length, t_color color, double reflectivity) {
    t_cube* cube = malloc(sizeof(t_cube));
    if (!cube) {
        fprintf(stderr, "Memory allocation failed for cube\n");
        return NULL;
    }

    t_shape* shape = malloc(sizeof(t_shape));
    if (!shape) {
        free(cube);
        fprintf(stderr, "Memory allocation failed for shape\n");
        return NULL;
    }

    t_object* obj = malloc(sizeof(t_object));
    shape->transformation = matrix_translation(center.x, center.y, center.z);
    shape->transformation = matrix_multiply(shape->transformation, matrix_scaling(edge_length, edge_length, edge_length));
    shape->material = material_create_default(&color, reflectivity);
    shape->material->reflectiv = reflectivity;

    shape->local_intersect = cube_intersect;
    shape->local_normal_at = cube_local_normal_at;

    obj->type = CUBE;
    obj->obj = cube;
    obj->shape = shape;

    return obj;
}


static void check_axis(double origin, double direction, double *tmin, double *tmax) {
    double tmin_numerator = (-1 - origin);
    double tmax_numerator = (1 - origin);

    if (fabs(direction) >= EPSILON) {
        *tmin = tmin_numerator / direction;
        *tmax = tmax_numerator / direction;
    } else {
        *tmin = tmin_numerator * INFINITY;
        *tmax = tmax_numerator * INFINITY;
    }

    if (*tmin > *tmax) {
        double temp = *tmin;
        *tmin = *tmax;
        *tmax = temp;
    }
}

static t_intersection* cube_intersect(t_object *obj, t_ray *ray, int *count) 
{

    double xtmin, xtmax, ytmin, ytmax, ztmin, ztmax;
    check_axis(ray->origin.x, ray->direction.x, &xtmin, &xtmax);
    check_axis(ray->origin.y, ray->direction.y, &ytmin, &ytmax);
    check_axis(ray->origin.z, ray->direction.z, &ztmin, &ztmax);

    double tmin = fmax(fmax(xtmin, ytmin), ztmin);
    double tmax = fmin(fmin(xtmax, ytmax), ztmax);

    if (tmin > tmax) {
        *count = 0;
        return NULL;
    }

    *count = 2;
    t_intersection *intersections = malloc(sizeof(t_intersection) * 2);
    intersections[0] = (t_intersection){tmin, obj};
    intersections[1] = (t_intersection){tmax, obj};
    return intersections;
}

t_tuple cube_local_normal_at(t_shape *cube, t_tuple point) 
{
    (void)cube;
    double abs_x = fabs(point.x);
    double abs_y = fabs(point.y);
    double abs_z = fabs(point.z);

    double maxc = fmax(fmax(abs_x, abs_y), abs_z);

    if (maxc == abs_x)
        return (t_tuple){copysign(1.0, point.x), 0, 0, 0};
    else if (maxc == abs_y)
        return (t_tuple){0, copysign(1.0, point.y), 0, 0};
    else
        return (t_tuple){0, 0, copysign(1.0, point.z), 0};
}
