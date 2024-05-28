/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:25:17 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/28 10:40:18 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

// Fonction pour multiplier deux matrices 4x4
t_matrix	matrix_mult(t_matrix Ma, t_matrix Mb)
{
	t_matrix	resultat;
	int			i;
	int			j;
	int			k;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			resultat.m[i][j] = 0;
			k = 0;
			while (k < 4)
			{
				resultat.m[i][j] += Ma.m[i][k] * Mb.m[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (resultat);
}

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

// fonction pour multiplier la matrices par un point ou vecteur.
t_tuple	matrix_mult_tuple(t_matrix mat, t_tuple tup)
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
