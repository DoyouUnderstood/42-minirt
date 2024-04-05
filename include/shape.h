#ifndef SHAPE_H
#define SHAPE_H

#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <float.h>

#include "main.h"
#include "graphics.h"
#include "mathematique.h"
#include "ray.h"
#include "minilibx.h"

typedef struct s_tuple t_tuple;
typedef struct s_ray t_ray;
typedef struct s_matrix t_matrix;
typedef struct s_mlx t_mlx;

#define MAX_OBJECTS 10


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

typedef enum e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	INVALID_TYPE = -1,
}					t_obj_type;

typedef struct s_object
{
	t_obj_type		type;
	void			*obj;
	struct s_object	*next;
}					t_object;

typedef struct s_world {
    t_light* light;
    t_object** objects; // Tableau de pointeurs vers t_object
    int object_count;
} t_world;

typedef struct s_sphere 
{
    t_tuple center;
    double diameter;
    t_color color;
    t_matrix transform;
	t_material material;
} t_sphere;

typedef struct s_intersection
{
    double t;
    t_object *object;
}   t_intersection;

typedef struct s_computations {
    double t;
    t_object *object;
    t_tuple point;
    t_tuple over_point; 
    t_tuple eyev;    
    t_tuple normalv;
    bool inside;
} t_computations;



bool is_shadowed(const t_world *world, const t_tuple point);
void render(t_mlx *mlx, t_world *world, t_camera *camera);

void draw_pixel(t_mlx *mlx, int x, int y, t_color color);
// view.c 
t_matrix view_transform(t_tuple from, t_tuple to, t_tuple up);

//camera.c 
t_ray ray_for_pixel(const t_camera *camera, const t_matrix *inverse_transform, int px, int py);
t_camera camera_create(int hsize, int vsize, float fov);


t_color color_at(t_world *world, const t_ray *ray);
t_color shade_hit(t_world *world, t_computations *comps);
void prepare_computations(t_computations *comps, const t_intersection *intersection, const t_ray *ray);
// =========== SPHERE =============

t_intersection* intersect(const t_ray *ray, t_object *object, int* out_count);
t_intersection* sphere_intersect(const t_ray *ray, t_object *object, int* out_count);
t_sphere* 		sphere_create();
t_object*		object_create_for_sphere(const t_sphere* sphere);

// ========== TRANSFORMATION ===========

void 			set_transform(t_sphere *sphere, t_matrix new_transform);
void 			set_material(t_sphere *s, t_material m);

// ============ INTERSECT ==============

t_intersection 	intersection_create(double t, t_object *object);
t_intersection* intersect(const t_ray *ray, t_object *object, int* out_count);
t_intersection* hit(t_intersection* intersections, int count);

// ============= world =================

t_world* world_default();
t_world* world_create();
void world_add_object(t_world* world, t_object* object);
t_intersection* intersect_world(const t_world* world, const t_ray* ray, int* count);

#endif
