#include "../include/ray.h"
#include "maths.h"
#include <stdint.h>

// Fonction pour initialiser un rayon
t_ray	ray_create(t_tuple origin, t_tuple direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

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

// Fonction pour calculer le point à la distance t le long du rayon
t_tuple	t_point_position(const t_ray *ray, double t)
{
	t_tuple	displacement;

	displacement = vector_multiply(ray->direction, t);
	return (point_add_vector(ray->origin, displacement));
}

// fonction pour transformer un rayon suivant une matrix
t_ray	ray_transform(t_matrix mat, t_ray ray)
{
	t_ray	transformed_ray;

	transformed_ray.origin = matrix_mult(mat, ray.origin);
	transformed_ray.direction = matrix_mult(mat, ray.direction);
	return (transformed_ray);
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
	pixel = matrix_mult(*inverse_transform, (t_tuple){camera->half_width
			- xoffset, camera->half_height - yoffset, -1, 1});
	origin = matrix_mult(*inverse_transform, (t_tuple){0, 0, 0, 1});
	direction = vector_normalize(tuple_subtract(pixel, origin));
	return ((t_ray){origin, direction});
}
