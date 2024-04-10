#include "test_shape.h"
#include "../include/shape.h"

typedef struct s_plane {
    // Aucune propriété spécifique requise pour le moment, mais vous pouvez en ajouter ici si nécessaire.
} t_plane;


t_tuple local_normal_at_plane(void *object, t_tuple local_point) {
    (void)object; // Non utilisé car la normal est constante pour un plan
    (void)local_point; // Non utilisé pour la même raison
    return (t_tuple){.x = 0.0, .y = 1.0, .z = 0.0, .w = 0.0};
}

t_intersection* local_intersect_plane(void *object, t_ray ray) {
    t_plane *plane = (t_plane*)object;
    if (fabs(ray.direction.y) < EPSILON) {
        return NULL; // Rayon parallèle au plan ou coplanaire, donc pas d'intersection
    }

    double t = -ray.origin.y / ray.direction.y;
    if (t < 0) return NULL; // Intersection derrière le rayon

    t_intersection *intersections = malloc(sizeof(t_intersection));
    if (intersections == NULL) return NULL; // Gestion d'erreur d'allocation

    intersections->t = t;
    intersections->object = plane;
    return intersections;
}

t_shape *plane(void) {
    t_shape *shape = malloc(sizeof(t_shape));
    if (shape == NULL) return NULL; // Gestion d'erreur d'allocation

    t_plane *plane = malloc(sizeof(t_plane));
    if (plane == NULL) { // Gestion d'erreur d'allocation
        free(shape);
        return NULL;
    }

    shape->object = plane;
    shape->local_normal_at = local_normal_at_plane;
    shape->local_intersect = local_intersect_plane;

    return shape;
}