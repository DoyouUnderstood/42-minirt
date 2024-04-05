#include "../include/main.h"

#include "../include/graphics.h"
#include "../include/mathematique.h"
#include "../include/shape.h"

t_color color_at(t_world *world, const t_ray *ray) {
    // Initialisation locale de 't_computations'
    t_computations comput;
    int count = 0;
    t_intersection *intersections = intersect_world(world, ray, &count);

    if (!intersections || count == 0) {
        // Aucune intersection trouvée, retournez la couleur d'arrière-plan.
        return (t_color){0.0, 0.0, 0.0};
    }

    t_intersection *hit_inter = hit(intersections, count); // Trouve l'intersection la plus proche
    if (!hit_inter) {
        // Pas de hit valide trouvé
        return (t_color){0.0, 0.0, 0.0};
    }

    // Remplit 'comput' avec les informations de calcul pour l'intersection la plus proche
    prepare_computations(&comput, hit_inter, ray);

    // Calculez la couleur basée sur les calculs et retournez-la.
    t_color color = shade_hit(world, &comput);
    free(intersections);
    return color;
}


t_color shade_hit(t_world *world, t_computations *comps) 
{
    t_color color;
    t_sphere *sphere = (t_sphere *)(comps->object->obj);
    bool in_shadow = is_shadowed(world, comps->over_point);

    color = lighting(&sphere->material, world->light, &comps->over_point, &comps->eyev, &comps->normalv, in_shadow);
    return (color);
}


