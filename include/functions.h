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

t_color							calculate_ef_c(const t_lighting *params);
t_color							calculate_ambient(t_color ef_c,
									double ambient_intensity);
t_color							calculate_diffuse(t_color ef_c,
									double light_dot_normal, double intensity);
t_color							calculate_specular(t_specular_params *params);
t_specular_params				prepare_specular_params(t_lighting *params,
									t_tuple lightv);

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

// ============= world =================



#endif