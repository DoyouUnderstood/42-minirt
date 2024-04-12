#include "../include/main.h"

#include "../include/graphics.h"
#include "../include/mathematique.h"
#include "../include/shape.h"
#include "../object/test_shape.h"


t_color color_at(t_world *world,t_ray *ray) 
{
    int count = 0;
    t_color color;
    t_computations comput;
    t_intersection *intersections;
    t_intersection *hit_inter;

    intersections = intersect_world(world, ray, &count);

    if (!intersections || count == 0) 
    {
        free(intersections);
        return ((t_color){0.25, 0.25, 0.25});
    }
    hit_inter = hit(intersections, count);
    if (!hit_inter) 
    {
        free(intersections);
        return (t_color){0.0, 0.0, 0.0};
    }
    prepare_computations(&comput, hit_inter, ray);
    color = shade_hit(world, &comput);
    return (color);
}


t_color shade_hit(t_world *world, t_computations *comps)
{
    t_color color;
    bool in_shadow = is_shadowed(world, comps->over_point);
    color = lighting(&comps->object->shape->material, world->light, &comps->over_point, &comps->eyev, &comps->normalv, in_shadow);
    return color;
}


