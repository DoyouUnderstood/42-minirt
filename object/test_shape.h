#ifndef TEST_SHAPE_H
#define TEST_SHAPE_H

#include "../include/shape.h"
// #include "../include/mathematique.h"
// // #include "../include/graphics.h"

typedef struct s_ray t_ray;
typedef struct s_shape t_shape;
typedef struct s_object t_object;

typedef struct s_shape 
{
    t_matrix        transformation;
    t_material      material;
    t_ray           saved_ray;
    t_tuple (*local_normal_at)(t_shape *shape, t_tuple local_point); 
    t_intersection* (*local_intersect)(t_object *obj, t_ray *ray, int *count);
} t_shape;

t_plane *plane_create(void);
t_intersection* plane_local_intersect(t_object *obj, t_ray *ray, int *count);
t_tuple plane_local_normal_at();
t_sphere* create_sphere();
void    transformation_default(t_shape *shape);
void set_shape_transform(t_shape *shape, t_matrix transformation);
void shape_default_material(t_shape *shape);
void shape_set_material(t_shape *shape, t_material material);
t_intersection* intersect_shape(t_object *object, t_ray *ray, int *count);
t_intersection* local_intersect(t_object *obj, t_ray *ray, int *count);
t_tuple normal_at_shape(t_object *obj, t_tuple world_point);
t_tuple local_normal_at_sphere(t_shape *shape, t_tuple local_point);

t_shape *test_shape(void);
t_intersection* test_local_intersect(t_shape *shape, t_ray *local_ray, int *count);
t_tuple test_local_normal_at(t_shape *shape, t_tuple local_point);


#endif