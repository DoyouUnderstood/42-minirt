/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:33:47 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/26 19:04:30 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "camera.h"
# include "light.h"
# include "minilibx.h"
# include "object.h"

#define MAX_OBJECTS 30

typedef struct s_mlx	t_mlx;

typedef struct s_world
{
	int						hsize;
	int						vsize;
	t_camera				camera;
	t_amb_light				amb;
	t_light					light;
	t_mlx					*mlx;
	t_object				objects[MAX_OBJECTS];
	int						object_count;
}							t_world;

void	world_init(t_world *world);
char	*world_init_resolution(t_world *world, int width, int height);
char	*world_init_camera(t_world *world, t_camera_data *data);
char	*world_init_ambient(t_world *world, t_amb_light *data);
char	*world_init_light(t_world *world, t_light *data);
char	*world_validate(t_world *world);
char	*world_add_object(t_world *world, t_object *object);
void	world_intersect(t_world *world, t_ray *ray,
			t_intersection_arr *intersections);
void	draw_render_to_img(t_world *world, t_mlx *mlx);
int		refresh_display(t_world *world);

#endif
