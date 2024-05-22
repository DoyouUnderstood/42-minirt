/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:17:27 by ltd               #+#    #+#             */
/*   Updated: 2024/05/22 17:12:08 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "functions.h"

#include <math.h>
#include <stdlib.h>

t_camera	*camera_create(float fov_degrees, t_tuple pos, t_tuple dir,
	int vsize, int hsize)
{
	t_camera	*camera;
	float		half_view;
	float		aspect;

	camera = malloc(sizeof(*camera));
	if (!camera)
		return (NULL);
	camera->vsize = vsize;
	camera->hsize = hsize;
	camera->fov = fov_degrees * M_PI / 180.0;
	camera->position = pos;
	camera->direction = dir;
	camera->transform = view_transform(pos, dir, vector_create(0, 1, 0));
	half_view = tan(camera->fov / 2.0);
	aspect = (float) camera->hsize / (float) camera->vsize;
	if (aspect >= 1)
	{
		camera->half_width = half_view;
		camera->half_height = half_view / aspect;
	}
	else
	{
		camera->half_width = half_view * aspect;
		camera->half_height = half_view;
	}
	camera->pixel_size = (camera->half_width * 2) / camera->hsize;
	return (camera);
}
