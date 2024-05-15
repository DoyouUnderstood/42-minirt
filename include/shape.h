#ifndef SHAPE_H
# define SHAPE_H

# include "light.h"
# include "material.h"
# include "minilibx.h"
# include "object.h"
# include "ray.h"
# include "types.h"
# include <float.h>
# include <limits.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_plane		t_plane;
typedef struct s_shape		t_shape;
typedef struct s_tuple		t_tuple;
typedef struct s_matrix		t_matrix;
typedef struct s_mlx		t_mlx;
typedef struct s_color		t_color;
typedef struct s_object		t_object;
typedef struct s_ray		t_ray;
typedef struct s_cylinder	t_cylinder;

# define MAX_OBJECTS 30

typedef struct s_material_specs
{
	t_color					color;
	double					reflectivity;
	t_pattern				*pattern;
	double					diameter;
	double					height;
}							t_material_specs;

t_cylinder					*create_cylinder(t_tuple center, double diameter,
								double height, t_tuple axis);

typedef struct s_world
{
	int						vsize;
	int						hsize;
	t_camera				*camera;
	t_mlx					*mlx;
	t_light					*light;
	t_object				**objects;
	int						object_count;
	t_amb_light				*amb;
}							t_world;

typedef struct s_intersection
{
	double					t;
	t_object				*obj;
}							t_intersection;

typedef struct s_computations
{
	double					t;
	t_object				*object;
	t_tuple					point;
	t_tuple					over_point;
	t_tuple					eyev;
	t_tuple					normalv;
	t_tuple					reflectv;
	t_color					*color;
	bool					inside;
}							t_computations;

t_matrix					matrix_rotation_axis(t_tuple axis, double angle);

t_color						reflected_color(t_world *world,
								const t_computations *comps, int remaining);

void						draw_render_to_img(t_world *world, t_mlx *mlx);
t_material					*material_create_default_plane(t_color *color,
								t_pattern *pattern);
t_intersection				*local_intersect_sphere(t_object *obj, t_ray *ray,
								int *out_count);

t_shape						*test_shape(void);

t_tuple						normal_at(t_object *obj, t_tuple world_point);

bool						is_shadowed(t_world *world, const t_tuple point);
void						render(t_world *world);

void						draw_pixel(t_mlx *mlx, int x, int y, t_color color);
// view.c
t_matrix					view_transform(t_tuple from, t_tuple to,
								t_tuple up);

// camera.c
t_ray						ray_for_pixel(const t_camera *camera,
								const t_matrix *inverse_transform, int px,
								int py);
t_camera					*camera_create(float fov_degrees, t_tuple position,
								t_tuple direction);

t_color						color_at(t_world *world, t_ray *ray, int remaining);
t_color						shade_hit(t_world *world, t_computations *comps,
								int remaining);
void						prepare_computations(t_computations *comps,
								const t_intersection *intersection,
								const t_ray *ray);
int							compare_intersections(const void *a, const void *b);
// object
t_object					*object_create_for_plane(t_color color,
								t_tuple center, t_pattern *pattern,
								t_tuple dir);
t_object					*object_create_for_sphere(t_tuple center,
								double diameter, t_material_specs specs);

t_tuple						cylinder_local_normal_at(t_shape *shape,
								t_tuple local_point);
t_intersection				*cylinder_intersect(t_object *obj, t_ray *ray,
								int *count);

// =========== SPHERE =============

t_intersection				*sphere_intersect(t_object *obj, t_ray *ray,
								int *out_count);
t_sphere					*sphere_create(void);

// ========== TRANSFORMATION ===========

void						set_transform(t_object *object, t_matrix transform);
void						set_material(t_sphere *s, t_material m);

// ============ INTERSECT ==============

t_intersection				*intersect_shape(t_object *object, t_ray *ray,
								int *count);
t_intersection				intersection_create(double t, t_object *obj);
t_intersection				*intersect(t_ray *ray, t_object *obj,
								int *out_count);
t_intersection				*hit(t_intersection *intersections, int count);

// ============= world =================

t_world						*world_default(void);
t_world						*world_create(void);
void						world_add_object(t_world *world, t_object *object);
t_intersection				*intersect_world(t_world *world, t_ray *ray,
								int *count);

#endif
