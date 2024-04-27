#include "../include/mathematique.h"
#include "maths.h"

// fonction pour cree un point.
t_tuple point_create(double x, double y, double z) 
{
    
    return (t_tuple){x, y, z, 1.0};
}

//addition d'un point et d'un vecteur.
t_tuple point_add_vector(t_tuple point, t_tuple vect) {
    t_tuple result;
    result.x = point.x + vect.x;
    result.y = point.y + vect.y;
    result.z = point.z + vect.z;
    result.w = 1.0;
    return result;
}

//addition d'un point et d'un point.
t_tuple point_add_point(t_tuple point, t_tuple vect) {
    t_tuple result;
    result.x = point.x + vect.x;
    result.y = point.y + vect.y;
    result.z = point.z + vect.z;
    result.w = 1.0;
    return result;
}

// fonction pour soustraire des points
t_tuple point_sub(t_tuple point, t_tuple vect) 
{
    t_tuple result;
    result.x = point.x - vect.x;
    result.y = point.y - vect.y;
    result.z = point.z - vect.z;
    result.w = 0.0;
    return result;
}

//fonction de mise a l'echelle d'un point
t_tuple point_multiply(t_tuple a, double scalar)
{
    t_tuple result;

    result.x = a.x * scalar;
    result.y = a.y * scalar;
    result.z = a.z * scalar;
    result.w = a.w;

    return result;
}

// fonction pour soustraire un vecteur d'un point.
t_tuple point_sub_vector(t_tuple point, t_tuple vect) 
{
    return (t_tuple){point.x - vect.x, point.y - vect.y, point.z - vect.z, 1.0};
}
