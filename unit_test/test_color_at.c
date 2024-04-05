#include <criterion/criterion.h>
#include "../include/shape.h"

Test(color_at, color_at_color_when_ray_miss)
{
    t_world *world = world_default();
    t_ray *r = ray_create(point_create(0, 0, -5), vector_create(0, 1, 0));
    t_color *c = color_at(world, r);
    cr_expect_float_eq(c->r, 0, 1e-4,  "Rouge incorrect : attendu=%d, reçu=%f", 0, c->r);
    cr_expect_float_eq(c->g, 0, 1e-4,  "Vert incorrect : attendu=%d, reçu=%f", 0, c->g);
    cr_expect_float_eq(c->b, 0, 1e-4, "Bleu incorrect : attendu=%d, reçu=%f", 0, c->b);
}

Test(color_at, color_at_color_when_ray_touch)
{
    t_world *world = world_default();
    t_ray *r = ray_create(point_create(0, 0, -5), vector_create(0, 0, 1));
    t_color *c = color_at(world, r);
    cr_expect_float_eq(c->r, 0.38066, 1e-4,  "Rouge incorrect : attendu=%d, reçu=%f", 0, c->r);
    cr_expect_float_eq(c->g, 0.47583, 1e-4,  "Vert incorrect : attendu=%d, reçu=%f", 0, c->g);
    cr_expect_float_eq(c->b, 0.2855, 1e-4, "Bleu incorrect : attendu=%d, reçu=%f", 0, c->b);
}

Test(scene_tests, color_with_intersection_behind_ray) 
{
    // Initialisation du monde par défaut
    t_world *world = world_default();
    
    // Récupération et casting des objets dans le monde
    t_sphere *outer = (t_sphere *)world->objects[0]->obj;
    t_sphere *inner = (t_sphere *)world->objects[1]->obj;
    
    // Modification des propriétés des matériaux
    outer->material.ambient = 1.0;
    inner->material.ambient = 1.0;
    
    // Création du rayon
    t_ray *r = ray_create(point_create(0, 0, 0.75), vector_create(0, 0, -1));
    
    // Calcul de la couleur
    t_color *c = color_at(world, r);
    
    // Vérification que la couleur est égale à celle du matériau de l'objet "inner"
    cr_expect_float_eq(c->r, inner->material.color.r, 1e-4, "Rouge incorrect : attendu=%f, reçu=%f", inner->material.color.r, c->r);
    cr_expect_float_eq(c->g, inner->material.color.g, 1e-4, "Vert incorrect : attendu=%f, reçu=%f", inner->material.color.g, c->g);
    cr_expect_float_eq(c->b, inner->material.color.b, 1e-4, "Bleu incorrect : attendu=%f, reçu=%f", inner->material.color.b, c->b);
}
