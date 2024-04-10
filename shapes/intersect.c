#include "../include/shape.h"

t_intersection intersection_create(double t, t_object *obj) 
{
    t_intersection i;
    i.t = t;
    i.obj = obj;
    return i;
}


// // Fonction générique pour calculer l'intersection avec n'importe quelle forme
// t_intersection* intersect(t_ray *ray, t_object *object, int* out_count) {
//     // Utilisation polymorphique de local_intersect
//     return (object->shape->local_intersect(object->shape, ray, out_count));
// }



// Fonction pour identifier le hit parmi une collection d'intersections
t_intersection* hit(t_intersection* intersections, int count) 
{
    t_intersection* hit = NULL;
    double min_t = DBL_MAX;

    for (int i = 0; i < count; i++) {
        if (intersections[i].t > 0 && intersections[i].t < min_t) {
            hit = &intersections[i];
            min_t = intersections[i].t;
        }
    }

    return (hit);
}

t_color calculate_color(t_intersection *closest_hit, t_ray *ray, t_light *light) {
    if (closest_hit != NULL) {
        // Calcule le point d'impact.
        t_tuple hit_point = t_point_position(ray, closest_hit->t);
        // Calcule la normale au point d'impact directement via la structure t_shape.
        t_tuple normal = closest_hit->obj->shape->local_normal_at(closest_hit->obj->shape, hit_point);
        // Calcule la direction de l'oeil.
        t_tuple eye = vector_negate(ray->direction);
        // Utilise la fonction d'éclairage pour calculer la couleur au point d'impact.
        return lighting(&closest_hit->obj->shape->material, light, &hit_point, &eye, &normal, false);
    } else {
        return (t_color){0, 0, 0}; // Retourne du noir s'il n'y a pas d'intersection.
    }
}
