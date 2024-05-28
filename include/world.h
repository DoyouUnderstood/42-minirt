/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:33:47 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/28 12:06:22 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "camera.h"
# include "light.h"
# include "minilibx.h"
# include "object.h"

# define MAX_OBJECTS 30

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
}	t_world;

typedef struct s_world_builder
{
	t_world			*world;
	bool			resolution_set;
	bool			camera_set;
	bool			light_set;
	bool			ambient_light_set;
	t_camera_data	camera_data;
}	t_world_builder;

// World
void	world_init(t_world *world);
void	world_intersect(t_world *world, t_ray *ray,
			t_intersection_arr *intersections);

// World builder
void	world_builder_init(t_world_builder *builder, t_world *world);
char	*world_builder_set_resolution(t_world_builder *builder, int width,
			int height);
char	*world_builder_set_camera(t_world_builder *builder,
			t_camera_data *data);
char	*world_builder_set_ambient(t_world_builder *builder,
			t_amb_light *data);
char	*world_builder_set_light(t_world_builder *builder,
			t_light *data);
char	*world_builder_add_object(t_world_builder *builder, t_object *object);
char	*world_builder_build(t_world_builder *builder);

void	draw_render_to_img(t_world *world, t_mlx *mlx);
int		refresh_display(t_world *world);

#endif
