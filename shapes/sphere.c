#include "../include/shape.h"
#define EPSILON 0.001
#include "../object/test_shape.h"

t_intersection* intersect_shape(t_object *object, t_ray *ray, int *count);

t_tuple local_normal_at_sphere(t_shape *shape, t_tuple local_point);
// fonction qui cree une sphere.
// Crée une forme générique avec des comportements par défaut
t_shape* create_generic_shape() 
{
    t_shape* shape = malloc(sizeof(t_shape));
    if (!shape) return NULL;

    shape->transformation = matrix_init_identity();
    shape->material = material_create_default();
    // Ces fonctions devraient être remplacées par des implémentations spécifiques lors de la création d'un type de forme spécifique
    shape->local_intersect = NULL;
    shape->local_normal_at = NULL;
    return shape;
}
// Fonction spécifique pour créer une sphère
t_sphere* sphere_create() 
{
    t_sphere* sphere = malloc(sizeof(t_sphere));
    if (!sphere)
        error_exit("Erreur d'allocation pour t_sphere.");
    sphere->center = point_create(0, 0, 0);
    sphere->diameter = 1.0;

    return sphere;
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

// Crée un nouvel objet t_object pour une sphère
t_object* object_create_for_sphere(t_sphere* sphere) 
{
    t_object* obj = malloc(sizeof(t_object));
    if (obj == NULL) {
        error_exit("Failed to allocate memory for t_object");
    }
    obj->shape = malloc(sizeof(t_shape));
    obj->type = SPHERE;
    obj->obj = sphere;
    obj->shape->transformation = matrix_init_identity();
    obj->shape->material = material_create_default();
    obj->shape->local_intersect = local_intersect_sphere;
    obj->shape->local_normal_at = local_normal_at_sphere;

    return obj;
}



t_intersection* local_intersect_sphere(t_object *obj, t_ray *ray, int* out_count) {
    t_sphere* sphere = (t_sphere*)obj->obj;
    double a, b, c;
    calculate_abc(ray, sphere, &a, &b, &c);
    double discriminant = calculate_discriminant(a, b, c);

    if (discriminant < -EPSILON) {
        *out_count = 0;
        return NULL; // Pas d'intersection
    }

    double t1, t2;
    double sqrt_discriminant = sqrt(discriminant);
    t1 = (-b - sqrt_discriminant) / (2 * a);

    if (discriminant == 0) {
        // Cas d'une intersection tangentielle, enregistrer deux fois la même valeur de t
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





// Modification de la fonction d'intersection principale
t_intersection* intersect(t_ray *ray, t_object *obj, int* out_count) 
{
    // Appel de la fonction d'intersection spécifique à la forme
    return obj->shape->local_intersect(obj, ray, out_count);
}

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

t_intersection* sphere_intersect(t_object *obj, t_ray *ray, int* out_count) 
{
    
    t_sphere* sphere = (t_sphere*)obj->obj;
    t_tuple sphere_to_ray = tuple_subtract(ray->origin, sphere->center);
    double a = vector_dot(ray->direction, ray->direction);
    double b = 2 * vector_dot(ray->direction, sphere_to_ray);
    double c = vector_dot(sphere_to_ray, sphere_to_ray) - pow(sphere->diameter / 2, 2);

    double discriminant = b * b - 4 * a * c;

    if (discriminant < -EPSILON) {
        *out_count = 0;
        return NULL;
    }

    t_intersection* intersections = malloc(sizeof(t_intersection) * 2);
    if (!intersections) {
        printf("Debug: Memory allocation failed\n");
        *out_count = 0;
        return NULL;
    }

    double sqrt_discriminant = sqrt(discriminant);
    double t1 = (-b - sqrt_discriminant) / (2 * a);
    double t2 = (-b + sqrt_discriminant) / (2 * a);

    *out_count = (discriminant == 0) ? 1 : 2;
    intersections[0] = intersection_create(t1, obj);
    intersections[1] = intersection_create(t2, obj);


    return intersections;
}
