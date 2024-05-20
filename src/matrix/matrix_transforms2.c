/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transforms2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:25:21 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/16 16:25:09 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

#include <math.h>

// fonction qui crée une matrice de rotation autour de l'axe x.
t_matrix	matrix_rotation_x(double angle)
{
	t_matrix	matrix;
	double		costheta;
	double		sintheta;

	matrix = matrix_identity();
	costheta = cos(angle);
	sintheta = sin(angle);
	matrix.m[1][1] = costheta;
	matrix.m[1][2] = -sintheta;
	matrix.m[2][1] = sintheta;
	matrix.m[2][2] = costheta;
	return (matrix);
}

// fonction qui crée une matrice de rotation autour de l'axe y.
t_matrix	matrix_rotation_y(double angle)
{
	t_matrix	matrix;
	double		costheta;
	double		sintheta;

	matrix = matrix_identity();
	costheta = cos(angle);
	sintheta = sin(angle);
	matrix.m[0][0] = costheta;
	matrix.m[0][2] = sintheta;
	matrix.m[2][0] = -sintheta;
	matrix.m[2][2] = costheta;
	return (matrix);
}

// fonction qui crée une matrice de rotation autour de l'axe z.
t_matrix	matrix_rotation_z(double angle)
{
	t_matrix	matrix;
	double		costheta;
	double		sintheta;

	matrix = matrix_identity();
	costheta = cos(angle);
	sintheta = sin(angle);
	matrix.m[0][0] = costheta;
	matrix.m[0][1] = -sintheta;
	matrix.m[1][0] = sintheta;
	matrix.m[1][1] = costheta;
	return (matrix);
}
