#include "test_shape.h"
#include "../include/shape.h"
#include "../object/test_shape.h"
#include "../graphics/graphics.h"

#include <math.h>
#include <float.h>
#include <stdlib.h>


t_cylinder* create_cylinder(t_tuple center, double diameter, double height, t_tuple axis) {
    t_cylinder* cylinder = malloc(sizeof(t_cylinder));
    if (!cylinder)
        return NULL;
    
    cylinder->center = center;
    cylinder->axis = axis;
    cylinder->radius = diameter / 2.0;
    cylinder->height = height;
    return cylinder;
}

// t_object* create_cylinder_cap(t_cylinder *cylinder, t_color color) 
// {
//     t_tuple cap_center = vector_add(cylinder->center, vector_scale(cylinder->axis, cylinder->height / 2.0));

//     t_object* cap = malloc(sizeof(t_object));
//     if (!cap) error_exit("Failed to allocate memory for cap");

//     cap->type = PLANE;
//     cap->shape = malloc(sizeof(t_shape));
//     if (!cap->shape) {
//         free(cap);
//         error_exit("Failed to allocate memory for t_shape of cap");
//     }

//     cap->shape->transformation = matrix_translation(cap_center.x, cap_center.y, cap_center.z);
//     cap->shape->material = material_create_default(&color);
//     cap->shape->local_normal_at = plane_local_normal_at;
//     cap->shape->local_intersect = plane_local_intersect;

//     return cap;
// }



t_object* object_create_for_cylinder(t_tuple center, double diameter, double height, t_tuple axis, t_color color, double reflectiv, t_pattern *pattern) 
{
    t_cylinder *cylinder = create_cylinder(center, diameter, height, axis);
    if (cylinder == NULL) {
        error_exit("Failed to allocate memory for cylinder");
    }

    t_object* obj = malloc(sizeof(t_object));
    if (obj == NULL) {
        free(cylinder);
        error_exit("Failed to allocate memory for t_object");
    }
    obj->type = CYLINDER;
    obj->obj = cylinder;
    obj->shape = malloc(sizeof(t_shape));
    if (obj->shape == NULL) 
    {
        free(cylinder);
        free(obj);
        error_exit("Failed to allocate memory for t_shape");
    }

    obj->shape->transformation = matrix_translation(center.x, center.y, center.z);
    obj->shape->material = material_create_default(&color, reflectiv, pattern);
    cylinder->center = (t_tuple){0, 0, 0, 0};
    obj->shape->local_intersect = cylinder_intersect;
    obj->shape->local_normal_at = cylinder_local_normal_at;

    return obj;
}



// Fonction pour calculer la normale locale à un point sur un cylindre
t_tuple cylinder_local_normal_at(t_shape *shape, t_tuple local_point) 
{
    (void)shape;
    return (t_tuple){local_point.x, 0, local_point.z, 0};
}

// Fonction pour calculer les intersections d'un rayon avec un cylindre
t_intersection* cylinder_intersect(t_object *obj, t_ray *ray, int *count) 
{
    t_cylinder *cylinder = (t_cylinder *)obj->obj;
    double a = pow(ray->direction.x, 2) + pow(ray->direction.z, 2);
    double b = 2 * ray->origin.x * ray->direction.x + 2 * ray->origin.z * ray->direction.z;
    double radiusSquared = pow(cylinder->radius, 2);
    double c = pow(ray->origin.x, 2) + pow(ray->origin.z, 2) - radiusSquared;
    double discriminant = pow(b, 2) - 4 * a * c;

    if (fabs(a) < EPSILON || discriminant < 0) {
        *count = 0;
        return NULL;
    }

    double t0 = (-b - sqrt(discriminant)) / (2 * a);
    double t1 = (-b + sqrt(discriminant)) / (2 * a);

    // Après avoir calculé t0 et t1
    double y0 = ray->origin.y + t0 * ray->direction.y;
    double y1 = ray->origin.y + t1 * ray->direction.y;
    double half_height = cylinder->height / 2.0;

    if (y0 < -half_height || y0 > half_height) t0 = -1;
    if (y1 < -half_height || y1 > half_height) t1 = -1;


    t_intersection* intersections = malloc(2 * sizeof(t_intersection));
    if (!intersections) {
        *count = 0;
        return NULL;
    }

    intersections[0] = (t_intersection){t0, obj};
    intersections[1] = (t_intersection){t1, obj};
    *count = 2;
    return intersections;
}
