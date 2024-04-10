#include "../include/main.h"

#include "../include/graphics.h"
#include "../include/mathematique.h"
#include "../include/shape.h"

t_color color_at(t_world *world,t_ray *ray) {
    // Initialisation locale de 't_computations'
    t_computations comput;
    int count = 0;

    t_intersection *intersections = intersect_world(world, ray, &count);

    if (!intersections || count == 0) {
            free(intersections);

        // Aucune intersection trouvée, retournez la couleur d'arrière-plan.
        return (t_color){0.0, 0.0, 0.0};
    }

    t_intersection *hit_inter = hit(intersections, count); // Trouve l'intersection la plus proche
    if (!hit_inter) {
            free(intersections);

        // Pas de hit valide trouvé
        return (t_color){0.0, 0.0, 0.0};
    }

    // Remplit 'comput' avec les informations de calcul pour l'intersection la plus proche
    free(intersections);
    prepare_computations(&comput, hit_inter, ray);

    // Calculez la couleur basée sur les calculs et retournez-la.
    t_color color = shade_hit(world, &comput);
    return color;
}


t_color shade_hit(t_world *world, t_computations *comps) {
    t_color color;
    bool in_shadow = is_shadowed(world, comps->over_point);

    // Imprimer les informations clés pour le débogage
    // printf("In Shadow: %s\n", in_shadow ? "Yes" : "No");
    // printf("Material Color: (%f, %f, %f)\n", comps->object->shape->material.color.r, comps->object->shape->material.color.g, comps->object->shape->material.color.b);
    // printf("Light Position: (%f, %f, %f) and Intensity: (%f, %f, %f)\n", world->light->pos.x, world->light->pos.y, world->light->pos.z, world->light->intensity.r, world->light->intensity.g, world->light->intensity.b);
    // printf("Over Point: (%f, %f, %f)\n", comps->over_point.x, comps->over_point.y, comps->over_point.z);
    // printf("Eye Vector: (%f, %f, %f)\n", comps->eyev.x, comps->eyev.y, comps->eyev.z);
    // printf("Normal Vector: (%f, %f, %f)\n", comps->normalv.x, comps->normalv.y, comps->normalv.z);

    color = lighting(&comps->object->shape->material, world->light, &comps->over_point, &comps->eyev, &comps->normalv, in_shadow);
    
    // Imprimer la couleur résultante pour le débogage
    //printf("Resulting Color: (%f, %f, %f)\n", color.r, color.g, color.b);

    return color;
}


