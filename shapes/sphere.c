#include "../include/shape.h"

// fonction qui cree une sphere.
t_sphere* sphere_create() 
{
    t_sphere* sphere = allocate_and_report(sizeof(t_sphere), "allocation sphere\n");
    if (sphere == NULL) {
        error_exit("erreur allocation t_sphere\n");
        return NULL;
    }
    sphere->center = point_create(0, 0, 0);
    sphere->diameter = 1.0;
    // sphere->color = (t_color){.r = 1, .g = 0.1, .b = 1};
    sphere->transform = matrix_init_identity();
    sphere->material = material_create_default();

    return (sphere);
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
t_object* object_create_for_sphere(const t_sphere* sphere) {
    t_object* obj = allocate_and_report(sizeof(t_object), "object allocation, function object_create_for_sphere");
    if (obj == NULL) {
        error_exit("error allocate_and_report t_object sphere.c");
    }
    obj->type = SPHERE;
    obj->obj = (void*)sphere;
    obj->next = NULL;
    return obj;
}


// Fonction pour calculer l'intersection d'un rayon avec une sphère.
t_intersection* sphere_intersect(const t_ray *ray, t_object *object, int* out_count) {
    t_sphere* sphere = (t_sphere*)object->obj;
    double a, b, c;
    calculate_abc(ray, sphere, &a, &b, &c);
    double discriminant = calculate_discriminant(a, b, c);
    
    t_intersection* intersections = (t_intersection*)allocate_and_report(sizeof(t_intersection) * 2, "t_intersection, sphere_intersect");
    if (intersections == NULL)
        return NULL;

    if (discriminant >= 0) 
    {
        double sqrt_discriminant = sqrt(discriminant);
        double t1 = (-b - sqrt_discriminant) / (2 * a);
        double t2 = (-b + sqrt_discriminant) / (2 * a);

        intersections[0] = intersection_create(t1, object);

        if (discriminant == 0) 
        {
            intersections[1] = intersection_create(t1, object);
            *out_count = 2;
        } else if (discriminant > 0) {
            intersections[1] = intersection_create(t2, object);
            *out_count = 2;
        }
    } else 
    {
        free(intersections);
        intersections = NULL;
        *out_count = 0;
    }
    return (intersections);
}

// Fonction pour assigner un materiaux a une sphere
void set_material(t_sphere *s, t_material m) 
{
    s->material = m;
}
