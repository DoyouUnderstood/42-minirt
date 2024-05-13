#include "../include/main.h"

#include "graphics.h"
#include "../include/mathematique.h"
#include "../include/shape.h"
#include "../object/test_shape.h"

/**
 * Computes the color seen at a ray's intersection with the nearest object in the world, or returns ambient color if no hit.
 * Handles memory for intersections and calls shading functions for hit objects.
 */
t_color color_at(t_world *world, t_ray *ray, int remaining) 
{
    int count = 0;
    t_intersection *intersections = intersect_world(world, ray, &count);
    if (!intersections || count == 0) 
    {
        free(intersections);
        return (color_multiply_scalar(world->amb->color, world->amb->ambient));
    }
    t_intersection *hit_inter = hit(intersections, count);
    if (!hit_inter) {
        free(intersections);
        return (color_multiply_scalar(world->amb->color, world->amb->ambient));
    }
    t_computations comput;
    prepare_computations(&comput, hit_inter, ray);
    t_color color = shade_hit(world, &comput, remaining);
    free(intersections);
    return color;
}

/**
 * Calculates the color at a point of intersection, considering direct lighting and reflections based on object material and lighting conditions.
 * Accounts for shadowing to adjust the color intensity and adds reflective contributions from other objects.
 */
t_color shade_hit(t_world *world, t_computations *comps, int remaining) 
{
    bool in_shadow = is_shadowed(world, comps->over_point);
    t_color surface = lighting(comps->object->shape->material, comps->object, world->light, &comps->over_point, &comps->eyev, &comps->normalv, in_shadow);
    t_color reflected = reflected_color(world, comps, remaining);
    return color_add(surface, reflected);
}