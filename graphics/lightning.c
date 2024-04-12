#include "../include/graphics.h"
#include <stdio.h>
#include <math.h>

t_color lighting(const t_material *material, const t_object *object, const t_light *light, const t_tuple *position, const t_tuple *eyev, const t_tuple *normalv, bool in_shadow) {
    t_color effective_color;

    // Utilisez le motif si présent, sinon utilisez la couleur du matériau
    if (material->pattern.pattern_at) {
        effective_color = stripe_at_object(material->pattern, object, *position);
    } else {
        effective_color = color_multiply(material->color, light->intensity);
    }

    t_color ambient = color_multiply_scalar(effective_color, material->ambient);
    if (in_shadow) {
        return ambient;
    }

    t_tuple lightv = vector_normalize(tuple_subtract(light->pos, *position));
    double light_dot_normal = vector_dot(lightv, *normalv);
    t_color diffuse, specular;

    if (light_dot_normal < 0) {
        diffuse = (t_color){0, 0, 0};
        specular = (t_color){0, 0, 0};
    } else {
        diffuse = color_multiply_scalar(effective_color, material->diffuse * light_dot_normal);
        t_tuple reflectv = reflect(vector_negate(lightv), *normalv);
        double reflect_dot_eye = vector_dot(reflectv, *eyev);

        if (reflect_dot_eye > 0) {
            double factor = pow(reflect_dot_eye, material->shininess);
            specular = color_multiply_scalar(light->intensity, material->specular * factor);
        } else {
            specular = (t_color){0, 0, 0};
        }
    }

    return color_add(color_add(ambient, diffuse), specular);
}

