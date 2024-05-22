#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "color.h"
# include "ray.h"
# include "light.h"
# include "lighting.h"
# include "object.h"
# include "pattern.h"
# include "world.h"
# include "intersection.h"
# include "computation.h"

t_color							color_at(t_world *world, t_ray *ray,
									int remaining);
t_color							calculate_color(t_intersection *closest_hit,
									t_ray *ray, t_light *light);


t_color							calculate_ef_c(const t_lighting *params);
t_color							calculate_ambient(t_color ef_c,
									double ambient_intensity);
t_color							calculate_diffuse(t_color ef_c,
									double light_dot_normal, double intensity);
t_color							calculate_specular(t_specular_params *params);
t_specular_params				prepare_specular_params(t_lighting *params,
									t_tuple lightv);
t_object						*parse_cylinder(char **parts, t_object *obj);
t_pattern						*set_pattern(char *part1, char *part2,
									char *part3);
t_object						*parse_cube(char **parts);

// =========== RAY ============

t_ray	ray_init(t_mlx *mlx, int x, int y,
			double projection_plane_z);
// ============== NORMAL ===============

void					mlx_initialisation(t_world *world);

t_color						reflected_color(t_world *world,
								const t_computations *comps, int remaining);

void						draw_render_to_img(t_world *world, t_mlx *mlx);


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

t_color						color_at(t_world *world, t_ray *ray, int remaining);
t_color						shade_hit(t_world *world, t_computations *comps,
								int remaining);
void						prepare_computations(t_computations *comps,
								const t_intersection *intersection,
								const t_ray *ray);
int							compare_intersections(const void *a, const void *b);

// ============ INTERSECT ==============

t_intersection				*hit(t_intersection *intersections, int count);

// ============= world =================

t_intersection	*intersect_world(t_world *world, t_ray *ray,
					int *count);


#endif