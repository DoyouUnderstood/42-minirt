/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:17:27 by ltd               #+#    #+#             */
/*   Updated: 2024/05/28 11:55:49 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "functions.h"

#include <math.h>
#include <stdlib.h>

char	*camera_init(t_camera *camera, t_camera_data *d)
{
	float		half_view;
	float		aspect;

	if (d->hsize < 1 || d->vsize < 1 || d->fov < 1.0 || d->fov > 180.0)
		return ("Camera width and height positive , or Invalid camera FOV");
	camera->hsize = d->hsize;
	camera->vsize = d->vsize;
	camera->fov = d->fov * M_PI / 180.0;
	camera->position = d->position;
	camera->direction = d->direction;
	camera->transform = v_t(d->position, d->direction, vector_create(0, 1, 0));
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
	return (NULL);
}
