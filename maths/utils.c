#include "../include/mathematique.h"

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
