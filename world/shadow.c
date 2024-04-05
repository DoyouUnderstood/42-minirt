#include "../include/main.h"

#include "../include/graphics.h"
#include "../include/mathematique.h"
#include "../include/shape.h"
#include <math.h>

bool is_shadowed(const t_world *world, const t_tuple point) {
    t_tuple direction = tuple_subtract(world->light->pos, point);
    double distance = tuple_magnitude(&direction);
    direction = vector_normalize(direction);

    t_ray shadow_ray = ray_create(point, direction);
    
    int count = 0; // Initialiser le compteur
    t_intersection *intersections = intersect_world(world, &shadow_ray, &count);

    bool in_shadow = false;
    for (int i = 0; i < count; i++) {
        if (intersections[i].t > 0 && intersections[i].t < distance) {
            in_shadow = true;
            break;
        }
    }

    free(intersections); // Supposer une fonction de libération appropriée
    return in_shadow;
}


