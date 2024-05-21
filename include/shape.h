/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:45:28 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/21 05:48:54 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H

# include "intersection.h"
# include "color.h"
# include "light.h"
# include "material.h"
# include "minilibx.h"
# include "object.h"
# include "ray.h"
# include "cylinder.h"

# include <float.h>
# include <limits.h>
# include <pthread.h>
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
typedef struct s_intersection t_intersection;

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

typedef struct s_renderthread
{
	t_mlx					*mlx;
	t_world					*world;
	t_camera				*camera;
	t_matrix				inverse_transform;
	int						start_y;
	int						end_y;
}							t_renderthread;

typedef struct s_RenderSetup
{
	pthread_t				*threads;
	t_renderthread			*thread_data;
	t_matrix				inverse_transform;
	int						segment_height;
	int						num_threads;
	int						current_index;
}							t_RenderSetup;

typedef struct s_threadSetupParams
{
	t_renderthread			*thread_data;
	t_world					*world;
	t_matrix				inverse_transform;
	int						index;
	int						num_threads;
	int						segment_height;
}							t_threadSetupParams;

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

typedef struct s_intersectionParams
{
	double					a;
	double					b;
	double					c;
	double					discriminant;
	double					t0;
	double					t1;
	double					half_height;
}							t_intersectionParams;

typedef struct s_interesctionData
{
	double					y0;
	double					y1;
	double					half_height;
	t_intersectionParams	*p;
	t_object				*obj;
}							t_interesctionData;

bool						realoc_inter(t_intersection **intersections,
								int required_capacity, int *capacity);

t_matrix					matrix_rotation_axis(t_tuple axis, double angle);

t_color						reflected_color(t_world *world,
								const t_computations *comps, int remaining);

void						draw_render_to_img(t_world *world, t_mlx *mlx);
t_material					*material_create_default_plane(t_color *color,
								t_pattern *pattern);


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
void						camera_create(float fov_degrees, t_tuple position,
								t_tuple direction, t_camera **camera);

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

t_tuple						cylinder_local_normal_at(t_shape *shape,
								t_tuple local_point);
t_intersection				*cylinder_intersect(t_object *obj, t_ray *ray,
								int *count);

// ============ INTERSECT ==============

t_intersection				*intersect_shape(t_object *object, t_ray *ray,
								int *count);
t_intersection				*hit(t_intersection *intersections, int count);

// ============= world =================

t_world						*world_create(void);
void						world_add_object(t_world *world, t_object *object);
t_intersection				*intersect_world(t_world *world, t_ray *ray,
								int *count);

#endif
