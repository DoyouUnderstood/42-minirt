#include "../include/shapes.h"

// Fonction pour identifier le hit parmi une collection d'intersections
t_intersection* hit(t_intersection* intersections, int count) {
    t_intersection* hit = NULL;
    double min_t = DBL_MAX;

    for (int i = 0; i < count; i++) {
        if (intersections[i].t > 0 && intersections[i].t < min_t) {
            hit = &intersections[i];
            min_t = intersections[i].t;
        }
    }

    return hit;
}