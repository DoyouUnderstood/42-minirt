#include <criterion/criterion.h>
#include "../include/graphics.h"
#include "../include/shape.h"

Test(shadow_tests, intersection_in_shadow) {
    // Crée un monde par défaut
    t_world *w = world_default();

    // Configurer la lumière du monde
    w->light = point_light(point_create(0, 0, -10), color_create(1, 1, 1));

    // Crée deux sphères et les ajoute au monde
    t_sphere *s1 = sphere_create();
    world_add_object(w, s1);
    
    t_sphere *s2 = sphere();
    // Applique une transformation à la seconde sphère pour la placer en position
    set_transform(s2, translation(0, 0, 10));
    world_add_object(w, s2);

    // Crée un rayon qui intersecte la seconde sphère en position (0, 0, 5)
    t_ray r = ray(point_create(0, 0, 5), vector_create(0, 0, 1));
    t_intersection i = intersection(4, s2);

    // Prépare les calculs d'intersection
    t_computations comps = prepare_computations(i, r);

    // Appelle shade_hit avec les calculs préparés
    t_color c = shade_hit(w, &comps);

    // Vérifie que la couleur renvoyée est uniquement celle de la composante ambiante
    cr_assert(eq(c, color_create(0.1, 0.1, 0.1)), "shade_hit should return ambient color when in shadow");
}
