#include "../include/mathematique.h"
#include "../include/shape.h"
#include "../object/test_shape.h"


// Calcule le vecteur réfléchi à partir d'un vecteur incident et d'un vecteur normal
t_tuple reflect(t_tuple incident, t_tuple normal)
{
    double dot;
    t_tuple scaled_normal;
    t_tuple reflection;
    dot = vector_dot(incident, normal);
    scaled_normal = vector_scale(normal, 2 * dot);
    reflection = tuple_subtract(incident, scaled_normal);

    return (reflection);
}

t_color reflected_color(t_world *world, const t_computations *comps, int remaining)
{
    if (comps->object->shape->material.reflectiv == 0 || remaining <= 0) {
        return color_create(0, 0, 0);
    }

    t_ray reflect_ray = ray_create(comps->over_point, comps->reflectv);
    t_color color = color_at(world, &reflect_ray, remaining - 1);
    return color_multiply_scalar(color, comps->object->shape->material.reflectiv);
}

