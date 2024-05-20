/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:25:29 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/20 11:07:45 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ray.h"
#include "maths.h"
#include <stdint.h>

// fonction pour initialiser un rayon
t_ray	ray_init(t_mlx *mlx, int x, int y, double projection_plane_z)
{
	t_tuple	camera_position;
	double	pixel_world_x;
	double	pixel_world_y;
	t_tuple	pixel_target;
	t_ray	ray;

	camera_position = point_create(0, 0, -5);
	pixel_world_x = ((double)x / mlx->width - 0.5) * (mlx->width / 100);
	pixel_world_y = ((double)y / mlx->height - 0.5) * (mlx->height / 100);
	pixel_target = point_create(pixel_world_x, -pixel_world_y,
			projection_plane_z);
	ray.origin = camera_position;
	ray.direction = vector_normalize(tuple_subtract(pixel_target,
				camera_position));
	return (ray);
}

/**
 * Generates a ray through a specified pixel (px,
	py) on the camera's view plane,
	using the camera's inverse transformation matrix.

	* Returns a ray from the camera origin to the 3D world coordinates of the pixel.
 */

t_ray	ray_for_pixel(const t_camera *camera, const t_matrix *inverse_transform,
		int px, int py)
{
	double	xoffset;
	double	yoffset;
	t_tuple	pixel;
	t_tuple	origin;
	t_tuple	direction;

	xoffset = (px + 0.5) * camera->pixel_size;
	yoffset = (py + 0.5) * camera->pixel_size;
	pixel = matrix_mult_tuple(*inverse_transform, (t_tuple){camera->half_width
			- xoffset, camera->half_height - yoffset, -1, 1});
	origin = matrix_mult_tuple(*inverse_transform, (t_tuple){0, 0, 0, 1});
	direction = vector_normalize(tuple_subtract(pixel, origin));
	return ((t_ray){origin, direction});
}
