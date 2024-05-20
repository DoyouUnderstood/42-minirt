/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltd <ltd@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:17:27 by ltd               #+#    #+#             */
/*   Updated: 2024/05/15 17:17:37 by ltd              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../include/mathematique.h"
#include "../include/shape.h"
#include <math.h>

void	camera_create(float fov_degrees, t_tuple position, t_tuple direction,
		t_camera **cam)
{
	float	half_view;
	float	aspect;

	(*cam)->fov = fov_degrees * M_PI / 180.0;
	(*cam)->position = position;
	(*cam)->direction = direction;
	(*cam)->transform = view_transform(position, direction, vector_create(0, 1,
				0));
	half_view = tan((*cam)->fov / 2.0);
	aspect = (float)(*cam)->hsize / (float)(*cam)->vsize;
	if (aspect >= 1)
	{
		(*cam)->half_width = half_view;
		(*cam)->half_height = half_view / aspect;
	}
	else
	{
		(*cam)->half_width = half_view * aspect;
		(*cam)->half_height = half_view;
	}
	(*cam)->pixel_size = ((*cam)->half_width * 2) / (*cam)->hsize;
}
