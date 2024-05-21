/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_old.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:45:28 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/21 14:11:48 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_OLD_H
# define SHAPE_OLD_H

# include "intersection.h"
# include "color.h"
# include "light.h"
# include "material.h"
# include "minilibx.h"
# include "object.h"
# include "ray.h"
# include "cylinder.h"
# include "computation.h"

# include <float.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

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
