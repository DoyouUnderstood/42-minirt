/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transforms2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:25:21 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/15 17:34:03 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mathematique.h"
#include "maths.h"

// fonction qui crée une matrice de rotation autour de l'axe y.
t_matrix	matrix_rotation_y(double angle)
{
	t_matrix	matrix;
	double		costheta;
	double		sintheta;

	matrix = matrix_init_identity();
	costheta = cos(angle);
	sintheta = sin(angle);
	matrix.m[0][0] = costheta;
	matrix.m[0][2] = sintheta;
	matrix.m[2][0] = -sintheta;
	matrix.m[2][2] = costheta;
	return (matrix);
}

// fonction qui crée une matrice de rotation autour de l'axe x.
t_matrix	matrix_rotation_x(double angle)
{
	t_matrix	matrix;
	double		costheta;
	double		sintheta;

	matrix = matrix_init_identity();
	costheta = cos(angle);
	sintheta = sin(angle);
	matrix.m[1][1] = costheta;
	matrix.m[1][2] = -sintheta;
	matrix.m[2][1] = sintheta;
	matrix.m[2][2] = costheta;
	return (matrix);
}

t_matrix	matrix_translation(double dx, double dy, double dz)
{
	t_matrix	mat;

	mat.m[0][0] = 1;
	mat.m[0][1] = 0;
	mat.m[0][2] = 0;
	mat.m[0][3] = dx;
	mat.m[1][0] = 0;
	mat.m[1][1] = 1;
	mat.m[1][2] = 0;
	mat.m[1][3] = dy;
	mat.m[2][0] = 0;
	mat.m[2][1] = 0;
	mat.m[2][2] = 1;
	mat.m[2][3] = dz;
	mat.m[3][0] = 0;
	mat.m[3][1] = 0;
	mat.m[3][2] = 0;
	mat.m[3][3] = 1;
	return (mat);
}

void	set_transform(t_object *object, t_matrix transform)
{
	if (object && object->shape)
	{
		object->shape->transformation = transform;
	}
}
