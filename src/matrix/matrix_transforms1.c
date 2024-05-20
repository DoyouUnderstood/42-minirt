/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transforms1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:25:21 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/16 16:25:07 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

#include <math.h>

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

// fonction qui crée une matrice de mise à l'échelle.
t_matrix	matrix_scaling(double sx, double sy, double sz)
{
	t_matrix	matrix;

	matrix = matrix_identity();
	matrix.m[0][0] = sx;
	matrix.m[1][1] = sy;
	matrix.m[2][2] = sz;
	return (matrix);
}

t_matrix	matrix_shearing(t_shearing_params params)
{
	t_matrix	matrix;

	matrix = matrix_identity();
	matrix.m[0][1] = params.xy;
	matrix.m[0][2] = params.xz;
	matrix.m[1][0] = params.yx;
	matrix.m[1][2] = params.yz;
	matrix.m[2][0] = params.zx;
	matrix.m[2][1] = params.zy;
	return (matrix);
}
