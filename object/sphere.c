#include "test_shape.h"
#include "../include/shape.h"
#include "../object/test_shape.h"
#include "../graphics/graphics.h"

#include <math.h>
#include <float.h>
#include <stdlib.h>


t_sphere* create_sphere(t_tuple center, double diameter) {
    t_sphere* sphere = malloc(sizeof(t_sphere));
    if (!sphere) 
        return NULL;
    sphere->center = center;
    sphere->diameter = diameter;
    return sphere;
}

t_object* object_create_for_sphere(t_tuple center, double diameter, t_color color, double relfectiv) 
{
    t_sphere *sphere = create_sphere(center, diameter);
    if (sphere == NULL) {
        error_exit("Failed to allocate memory for sphere");
    }

    t_object* obj = malloc(sizeof(t_object));
    if (obj == NULL) {
        error_exit("Failed to allocate memory for t_object");
    }
    obj->type = SPHERE;
    obj->obj = sphere;

    obj->shape = malloc(sizeof(t_shape));
    if (obj->shape == NULL) {
        free(sphere);
        free(obj);
        error_exit("Failed to allocate memory for t_shape");
    }

    obj->shape->transformation = matrix_init_identity();
    obj->shape->material = material_create_default(&color, relfectiv);
    obj->shape->local_intersect = local_intersect_sphere;
    obj->shape->local_normal_at = local_normal_at_sphere;

    t_matrix translation = matrix_translation(center.x, center.y, center.z);
    t_matrix scaling = matrix_scaling(1, 1, 1);
    obj->shape->transformation = matrix_multiply(translation, scaling);
    sphere->center = (t_tuple){0,0,0,0};
    return obj;
}

// Calcule les coefficients 'a', 'b', et 'c' pour l'équation quadratique d'intersection.
void calculate_abc(const t_ray *ray, const t_sphere *sphere, double *a, double *b, double *c) {
    t_tuple sphere_to_ray = tuple_subtract(ray->origin, sphere->center);
    *a = vector_dot(ray->direction, ray->direction);
    *b = 2 * vector_dot(ray->direction, sphere_to_ray);
    *c = vector_dot(sphere_to_ray, sphere_to_ray) - pow(sphere->diameter, 2);
}


// Calcule le discriminant à partir des coefficients 'a', 'b', et 'c'.
double calculate_discriminant(double a, double b, double c) {
    return b * b - 4 * a * c;
}

t_intersection* local_intersect_sphere(t_object *obj, t_ray *ray, int* out_count) {
    t_sphere* sphere = (t_sphere*)obj->obj;
    double a, b, c;
    calculate_abc(ray, sphere, &a, &b, &c);
    double discriminant = calculate_discriminant(a, b, c);

    if (discriminant < -EPSILON) {
        *out_count = 0;
        return NULL;
    }

    double t1, t2;
    double sqrt_discriminant = sqrt(discriminant);
    t1 = (-b - sqrt_discriminant) / (2 * a);

    if (discriminant == 0) {
        *out_count = 2;
        t_intersection* intersections = malloc(sizeof(t_intersection) * (*out_count));
        if (!intersections) {
            *out_count = 0;
            return NULL;
        }
        intersections[0] = intersection_create(t1, obj);
        intersections[1] = intersection_create(t1, obj); // Même valeur pour une tangente
        return intersections;
    } else {
        // Deux intersections distinctes
        *out_count = 2;
        t_intersection* intersections = malloc(sizeof(t_intersection) * (*out_count));
        if (!intersections) {
            *out_count = 0;
            return NULL;
        }
        t2 = (-b + sqrt_discriminant) / (2 * a);
        intersections[0] = intersection_create(t1, obj);
        intersections[1] = intersection_create(t2, obj);
        return intersections;
    }
}


t_tuple local_normal_at_sphere(t_shape *shape, t_tuple local_point) 
{
    (void)shape;
    t_tuple tupl = tuple_subtract(local_point, point_create(0, 0, 0));
    return tupl;
}
