/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operation2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:25:17 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/15 17:32:38 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mathematique.h"
#include "maths.h"

t_matrix	matrix_transpose(t_matrix mat)
{
	int			i;
	int			j;
	t_matrix	transposed;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			transposed.m[j][i] = mat.m[i][j];
			j++;
		}
		i++;
	}
	return (transposed);
}

// fonction pour inverser les matrix.
t_matrix	matrix_inverse(t_matrix mat)
{
	double		det;
	t_matrix	cofactor;
	int			i;
	int			j;

	det = determinant4x4(mat);
	if (det == 0)
		return (matrix_init_identity());
	cofactor = calculate_cofactor_matrix(mat);
	cofactor = matrix_transpose(cofactor);
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			cofactor.m[i][j] /= det;
			j++;
		}
		i++;
	}
	return (cofactor);
}

// fonction pour multiplier la matrices par un point ou vecteur.
t_tuple	matrix_mult(t_matrix mat, t_tuple tup)
{
	t_tuple	result;

	result.x = mat.m[0][0] * tup.x + mat.m[0][1] * tup.y + mat.m[0][2] * tup.z
		+ mat.m[0][3] * tup.w;
	result.y = mat.m[1][0] * tup.x + mat.m[1][1] * tup.y + mat.m[1][2] * tup.z
		+ mat.m[1][3] * tup.w;
	result.z = mat.m[2][0] * tup.x + mat.m[2][1] * tup.y + mat.m[2][2] * tup.z
		+ mat.m[2][3] * tup.w;
	result.w = mat.m[3][0] * tup.x + mat.m[3][1] * tup.y + mat.m[3][2] * tup.z
		+ mat.m[3][3] * tup.w;
	return (result);
}
