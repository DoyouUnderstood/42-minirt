/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:17:27 by ltd               #+#    #+#             */
/*   Updated: 2024/05/25 06:19:52 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "functions.h"

#include <math.h>
#include <stdlib.h>

char	*camera_init(t_camera *camera, t_camera_data *data)
{
	float		half_view;
	float		aspect;

	if (data->hsize < 1 || data->vsize < 1)
		return ("Camera width and height must be positive numbers");
	if (data->fov < 1.0 || data->fov > 180.0)
		return ("Invalid camera FOV");
	camera->hsize = data->hsize;
	camera->vsize = data->vsize;
	camera->fov = data->fov * M_PI / 180.0;
	camera->position = data->position;
	camera->direction = data->direction;
	camera->transform = view_transform(data->position, data->direction, vector_create(0, 1, 0));
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
