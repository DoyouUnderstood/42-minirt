#ifndef MATHEMATIQUE_H
#define MATHEMATIQUE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "minilibx.h"
#include "object.h"
#include "../maths/maths.h"
#define TUPLE_EPSILON 1e-6

typedef struct s_sphere t_sphere;
typedef struct s_intersection t_intersection;

typedef struct s_mlx t_mlx;
typedef struct s_material t_material;


typedef struct s_ray 
{
    t_tuple origin;
    t_tuple direction;
} t_ray;


typedef struct s_shape 
{
    t_matrix        transformation;
    t_material      *material;
    t_ray           saved_ray;
    t_tuple (*local_normal_at)(t_shape *shape, t_tuple local_point); 
    t_intersection* (*local_intersect)(t_object *obj, t_ray *ray, int *count);
} t_shape;

#endif