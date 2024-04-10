#include <criterion/criterion.h>
#include "../include/shape.h"

Test(ray_tracing, hit_when_an_intersection_happens_on_the_outside) {
    t_ray r = ray_create(point_create(0, 0, -5), vector_create(0, 0, 1));
    t_sphere* sphere = sphere_create();
    t_object* object = object_create_for_sphere(sphere);
    t_intersection i = intersection_create(4, object);
    t_computations comps;
    prepare_computations(&comps, &i, &r); // Implémentez cette fonction selon la description.
    
    cr_assert_not(comps.inside, "comps->inside devrait être false pour une intersection à l'extérieur.");
}


Test(ray_tracing, hit_when_an_intersection_happens_on_the_inside) {
    t_ray r = ray_create(point_create(0, 0, 0), vector_create(0, 0, 1));
    t_sphere* sphere = sphere_create(); // La sphère est centrée à l'origine par défaut.
    t_object* object = object_create_for_sphere(sphere);
    t_intersection i = intersection_create(1, object);
    
    t_computations comps;
    prepare_computations(&comps, &i, &r);
    
    cr_assert_eq(comps.point.x, 0, "Le point d'intersection x devrait être 0.");
    cr_assert_eq(comps.point.y, 0, "Le point d'intersection y devrait être 0.");
    cr_assert_eq(comps.point.z, 1, "Le point d'intersection z devrait être 1.");
    cr_assert_eq(comps.eyev.x, 0, "Le vecteur eyev x devrait être 0.");
    cr_assert_eq(comps.eyev.y, 0, "Le vecteur eyev y devrait être 0.");
    cr_assert_eq(comps.eyev.z, -1, "Le vecteur eyev z devrait être -1.");
    cr_assert(comps.inside, "comps->inside devrait être vrai pour une intersection à l'intérieur.");
    cr_assert_eq(comps.normalv.x, 0, "Le vecteur normal x devrait être 0.");
    cr_assert_eq(comps.normalv.y, 0, "Le vecteur normal y devrait être 0.");
    cr_assert_eq(comps.normalv.z, -1, "Le vecteur normal z devrait être -1, car il est inversé.");
}

Test(shade_hit, shading_an_intersection) 
{
    t_world *w = world_default();
    t_ray r = ray_create(point_create(0, 0, -5), vector_create(0, 0, 1));
    t_object *obj = w->objects[0];
    t_intersection i = intersection_create(4, obj);
    w->objects[1]->shape->material.color.g = 0.8;

    t_computations comps;
    prepare_computations(&comps, &i, &r);
    t_color c = shade_hit(w, &comps);
    
    cr_assert_float_eq(c.r, 0.38066, 1e-5, "Rouge incorrect : attendu=%f, reçu=%f", 0.38066, c.r);
    cr_assert_float_eq(c.g, 0.47583, 1e-5, "Vert incorrect : attendu=%f, reçu=%f", 0.47583, c.g);
    cr_assert_float_eq(c.b, 0.2855, 1e-5, "Bleu incorrect : attendu=%f, reçu=%f", 0.2855, c.b);
}




Test(shade_hit, shading_an_intersection_from_the_inside) 
{
    t_world *w = world_default();
    t_light *new_light = light_create((t_color){1, 1, 1}, point_create(0, 0.25, 0));
    if (w->light) {
        free(w->light);
    }

    w->light = new_light;
    t_ray r = ray_create(point_create(0, 0, 0), vector_create(0, 0, 1));
    t_object *shape = w->objects[1];
    t_intersection i = intersection_create(0.5, shape);
    t_computations comps;
    prepare_computations(&comps, &i, &r);
    t_color c = shade_hit(w, &comps);
    cr_assert_float_eq(c.r, 0.90498, 1e-5, "Rouge incorrect : attendu=%f, reçu=%f", 0.90498, c.r);
    cr_assert_float_eq(c.g, 0.90498, 1e-5, "Vert incorrect : attendu=%f, reçu=%f", 0.90498, c.g);
    cr_assert_float_eq(c.b, 0.90498, 1e-5, "Bleu incorrect : attendu=%f, reçu=%f", 0.90498, c.b);

}

