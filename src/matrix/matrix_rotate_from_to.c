/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotate_from_to.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:25:21 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/21 10:56:29 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "tuple.h"

#include <math.h>

static void	matrix_rotation_axis2(t_matrix *rot)
{
	rot->m[2][3] = 0;
	rot->m[3][0] = 0;
	rot->m[3][1] = 0;
	rot->m[3][2] = 0;
	rot->m[3][3] = 1;
}

// Création d'une matrice de rotation autour d'un axe par un angle
t_matrix	matrix_rotation_axis(t_tuple axis, double angle)
{
	double		cos_theta;
	double		sin_theta;
	double		one_minus_cos;
	t_matrix	rot;

	axis = vector_normalize(axis);
	cos_theta = cos(angle);
	sin_theta = sin(angle);
	one_minus_cos = 1.0 - cos_theta;
	rot.m[0][0] = cos_theta + axis.x * axis.x * one_minus_cos;
	rot.m[0][1] = axis.x * axis.y * one_minus_cos - axis.z * sin_theta;
	rot.m[0][2] = axis.x * axis.z * one_minus_cos + axis.y * sin_theta;
	rot.m[0][3] = 0;
	rot.m[1][0] = axis.y * axis.x * one_minus_cos + axis.z * sin_theta;
	rot.m[1][1] = cos_theta + axis.y * axis.y * one_minus_cos;
	rot.m[1][2] = axis.y * axis.z * one_minus_cos - axis.x * sin_theta;
	rot.m[1][3] = 0;
	rot.m[2][0] = axis.z * axis.x * one_minus_cos - axis.y * sin_theta;
	rot.m[2][1] = axis.z * axis.y * one_minus_cos + axis.x * sin_theta;
	rot.m[2][2] = cos_theta + axis.z * axis.z * one_minus_cos;
	matrix_rotation_axis2(&rot);
	return (rot);
}

// Utilitaire pour calculer la matrice de rotation d'un vecteur à un autre
t_matrix	matrix_rotate_from_to(t_tuple from, t_tuple to)
{
	t_tuple	axis;
	double	angle;

	axis = vector_cross(from, to);
	angle = acos(vector_dot(vector_normalize(from), vector_normalize(to)));
	return (matrix_rotation_axis(axis, angle));
}
