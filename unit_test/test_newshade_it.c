#include <criterion/criterion.h>
#include "../include/graphics.h"
#include "../include/shape.h"
#include "../object/test_shape.h"

Test(shadow_tests, intersection_in_shadow) {
    // Crée un monde par défaut
    t_world *w = world_default();

    // Configurer la lumière du monde
    w->light = light_create((t_color){1, 1, 1},point_create(0, 0, -10));

    // Crée deux sphères et les ajoute au monde    
    set_shape_transform(w->objects[1]->shape, matrix_translation(0, 0, 10));

    // Crée un rayon qui intersecte la seconde sphère en position (0, 0, 5)
    t_ray r = ray_create(point_create(0, 0, 5), vector_create(0, 0, 1));
    t_intersection i = intersection_create(4, w->objects[1]);

    // Prépare les calculs d'intersection
    t_computations comps;
    prepare_computations(&comps, &i, &r);

    // Appelle shade_hit avec les calculs préparés
    t_color c = shade_hit(w, &comps);

    // Vérifie que la couleur renvoyée est uniquement celle de la composante ambiante
cr_assert_float_eq(c.r, 0.1, 1e-6, "shade_hit should return ambient color when in shadow (red channel incorrect)");
cr_assert_float_eq(c.g, 0.1, 1e-6, "shade_hit should return ambient color when in shadow (green channel incorrect)");
cr_assert_float_eq(c.b, 0.1, 1e-6, "shade_hit should return ambient color when in shadow (blue channel incorrect)");
}
