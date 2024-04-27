#include "../include/mathematique.h"
#include "../include/shape.h"
#include "graphics.h"
// fonction for create material struct with default values
t_material *material_create_default(t_color *color) 
{
    t_material *m = malloc(sizeof(t_material));

    m->color = *color;
    m->amb.color = (t_color){0, 0, 1};
    m->amb.ambient = 0.3;
    m->diffuse = 0;
    m->specular = 0.9;
    m->shininess = 200.0;
    m->reflectiv = 1.0;
    m->pattern = NULL;
    m->refractive_index = 1.0;
    m->transparency = 0.0;

    return m;
}


t_material *material_create_default_plane(t_color *color) 
{
    t_material *m = malloc(sizeof(t_material));
    t_pattern *pattern = checker_pattern_create(color_create(0, 0, 0), color_create(1, 1, 1));

    m->color = *color;
    m->amb.color = (t_color){1, 1, 1};
    m->amb.ambient = 0.3;
    // /-> m.diffuse = 0.9;
    m->specular = 0.9;
    m->shininess = 200.0;
    m->reflectiv = 0.5;
    m->refractive_index = 0.0;
    m->transparency = 0.0;
    m->pattern = pattern;

    return (m);
}
