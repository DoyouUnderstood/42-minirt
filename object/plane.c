#include "test_shape.h"
#include "../include/shape.h"
#include "../object/test_shape.h"
#include "../graphics/graphics.h"

// Création d'une matrice de rotation autour d'un axe par un angle
t_matrix matrix_rotation_axis(t_tuple axis, double angle) {
    axis = vector_normalize(axis);
    double cos_theta = cos(angle);
    double sin_theta = sin(angle);
    double one_minus_cos = 1.0 - cos_theta;

    t_matrix R;
    R.m[0][0] = cos_theta + axis.x * axis.x * one_minus_cos;
    R.m[0][1] = axis.x * axis.y * one_minus_cos - axis.z * sin_theta;
    R.m[0][2] = axis.x * axis.z * one_minus_cos + axis.y * sin_theta;
    R.m[0][3] = 0;
    R.m[1][0] = axis.y * axis.x * one_minus_cos + axis.z * sin_theta;
    R.m[1][1] = cos_theta + axis.y * axis.y * one_minus_cos;
    R.m[1][2] = axis.y * axis.z * one_minus_cos - axis.x * sin_theta;
    R.m[1][3] = 0;
    R.m[2][0] = axis.z * axis.x * one_minus_cos - axis.y * sin_theta;
    R.m[2][1] = axis.z * axis.y * one_minus_cos + axis.x * sin_theta;
    R.m[2][2] = cos_theta + axis.z * axis.z * one_minus_cos;
    R.m[2][3] = 0;
    R.m[3][0] = 0;
    R.m[3][1] = 0;
    R.m[3][2] = 0;
    R.m[3][3] = 1;

    return R;
}

t_material *material_create_default_plane(t_color *color, t_pattern *pattern);

// Utilitaire pour calculer la matrice de rotation d'un vecteur à un autre
t_matrix rotate_from_to(t_tuple from, t_tuple to) {
    t_tuple axis = vector_cross(from, to);
    double angle = acos(vector_dot(vector_normalize(from), vector_normalize(to)));
    return matrix_rotation_axis(axis, angle);
}

// Intégration dans la création de l'objet Plane
t_object* object_create_for_plane(t_color color, t_tuple center, t_pattern *pattern, t_tuple direction) {
    t_plane *plane = plane_create(center);
    t_object *obj = (t_object *)malloc(sizeof(t_object));
    if (!obj) 
        return NULL;
    
    obj->type = PLANE;
    obj->obj = plane;
    obj->shape = (t_shape *)malloc(sizeof(t_shape));
    if (!obj->shape) {
        free(obj);
        return NULL;
    }

    // La normale par défaut (ex: vers le haut si le plan est horizontal)
    t_tuple default_normal = {0, 1, 0, 0};
    
    // Calculer la rotation pour aligner la normale par défaut avec la direction fournie
    t_matrix rotation = rotate_from_to(default_normal, direction);
    t_matrix translation = matrix_translation(center.x, center.y, center.z);
    
    // Appliquer la rotation puis la translation
    obj->shape->transformation = matrix_multiply(translation, rotation);

    obj->shape->material = material_create_default_plane(&color, pattern);
    obj->shape->local_normal_at = plane_local_normal_at;
    obj->shape->local_intersect = plane_local_intersect;

    return obj;
}


t_plane *plane_create(t_tuple center)
{
    t_plane *plane = malloc(sizeof(t_plane));
    plane->center = center;
    return (plane);
}

t_tuple plane_local_normal_at(t_shape *shape, t_tuple local_point) 
{
    (void)local_point;
    (void)shape;
    return vector_create(0, 1, 0);
}


t_intersection* plane_local_intersect(t_object *obj, t_ray *ray, int *count) {
    if (fabs(ray->direction.y) < TUPLE_EPSILON) {
        *count = 0;
        return NULL;
    }

    double t = -ray->origin.y / ray->direction.y;
    
    *count = 1;
    t_intersection *intersections = (t_intersection *)malloc(sizeof(t_intersection));
    if (!intersections) {
        *count = 0;
        return NULL;
    }
    intersections[0] = (t_intersection){t, obj};

    return intersections;
}
