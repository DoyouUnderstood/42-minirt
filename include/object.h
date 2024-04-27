#ifndef OBJECT_H
#define OBJECT_H

#include "mathematique.h"
#include "ray.h"
#include "shape.h"
#include "types.h"

#define EPSILON 0.00001
typedef struct s_shape t_shape;
typedef struct s_ray   t_ray;
typedef struct s_color t_color;


typedef struct s_cube 
{

} t_cube;



typedef struct s_sphere 
{
    t_tuple center;
    double diameter;
} t_sphere;

typedef enum e_obj_type
{
    SPHERE, 
    CYLINDER,
    PLANE,
    CUBE,
    INVALID_TYPE

}t_obj_type;

typedef struct s_object 
{
   t_obj_type type;
    void *obj;
    t_shape *shape;
} t_object;

typedef struct s_plane 
{
    t_tuple center;
} t_plane;

typedef struct s_cylinder {
    t_tuple center;
    t_tuple axis;
    double radius;
    double height;
} t_cylinder;

typedef struct s_camera 
{
    double hsize;
    double vsize;
    double fov;
    float pixel_size;
    float half_width;
    float half_height;
    t_matrix transform;
    t_tuple position;
    t_tuple direction;
} t_camera;

t_object* create_cube();

t_object* object_create_for_cylinder(t_tuple center, double diameter, double height, t_tuple axis, t_color color);

t_tuple cube_local_normal_at(t_shape *cube, t_tuple point);

#endif