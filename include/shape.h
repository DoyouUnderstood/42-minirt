#ifndef SHAPE_H
#define SHAPE_H

#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <float.h>

// #include "main.h"
#include "graphics.h"
#include "mathematique.h"
#include "minilibx.h"
// #include "../object/test_shape.h"
#include "ray.h"


typedef struct s_shape t_shape;
typedef struct s_tuple t_tuple;
// typedef struct s_ray t_ray;
typedef struct s_matrix t_matrix;
typedef struct s_mlx t_mlx;

#define MAX_OBJECTS 10

typedef enum e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	INVALID_TYPE = -1,
}					t_obj_type;


typedef struct s_object 
{
    t_obj_type type;
    void *obj;
    t_shape *shape;
} t_object;





t_sphere* create_sphere();

typedef struct s_camera
{
    double hsize;
    double vsize;
    double fov;
    float pixel_size; 
    float half_width; 
    float half_height;
    t_matrix transform;
}                   t_camera;


typedef struct s_world {
    t_light* light;
    t_object** objects;
    int object_count;
} t_world;



typedef struct s_plane 
{
    t_tuple center;
    t_color color;
} t_plane;


typedef struct s_sphere 
{
    t_tuple center;
    double diameter;
    t_color color;
} t_sphere;

typedef struct s_intersection {
    double t;
    t_object *obj;
} t_intersection;


typedef struct s_computations {
    double t;
    t_object *object;
    t_tuple point;
    t_tuple over_point; 
    t_tuple eyev;    
    t_tuple normalv;
    bool inside;
} t_computations;


t_material material_create_default_plane();
t_intersection* local_intersect_sphere( t_object *obj, t_ray *ray, int* out_count);

t_shape *test_shape(void);

t_tuple normal_at(t_object *obj, t_tuple world_point);


bool is_shadowed(t_world *world, const t_tuple point);
void render(t_mlx *mlx, t_world *world, t_camera *camera);

void draw_pixel(t_mlx *mlx, int x, int y, t_color color);
// view.c 
t_matrix view_transform(t_tuple from, t_tuple to, t_tuple up);

//camera.c 
t_ray ray_for_pixel(const t_camera *camera, const t_matrix *inverse_transform, int px, int py);
t_camera *camera_create(int hsize, int vsize, float fov);


t_color color_at(t_world *world, t_ray *ray);
t_color shade_hit(t_world *world, t_computations *comps);
void prepare_computations(t_computations *comps, const t_intersection *intersection, const t_ray *ray);

// object
t_object* object_create_for_plane(t_plane *plane);
t_object* object_create_for_sphere(t_sphere* sphere);

// =========== SPHERE =============

t_intersection* sphere_intersect(t_object *obj, t_ray *ray, int* out_count);
t_sphere* 		sphere_create();
t_object* object_create_for_sphere(t_sphere* sphere);

// ========== TRANSFORMATION ===========

void 			set_transform(t_sphere *sphere, t_matrix new_transform);
void 			set_material(t_sphere *s, t_material m);

// ============ INTERSECT ==============

t_intersection* intersect_shape(t_object *object, t_ray *ray, int *count);
t_intersection intersection_create(double t, t_object *obj);
t_intersection* intersect(t_ray *ray, t_object *obj, int* out_count); 
t_intersection* hit(t_intersection* intersections, int count);

// ============= world =================

t_world* world_default();
t_world* world_create();
void world_add_object(t_world* world, t_object* object);
t_intersection* intersect_world(t_world* world, t_ray* ray, int* count);

#endif
