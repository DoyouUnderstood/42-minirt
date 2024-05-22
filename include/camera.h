/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:26:50 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/22 17:10:51 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "matrix.h"
# include "tuple.h"

typedef struct s_camera
{
	double		hsize;
	double		vsize;
	double		fov;
	float		pixel_size;
	float		half_width;
	float		half_height;
	t_matrix	transform;
	t_tuple		position;
	t_tuple		direction;
}	t_camera;

t_camera	*camera_create(float fov_degrees, t_tuple position,
				t_tuple direction, int vsize, int hsize);

#endif