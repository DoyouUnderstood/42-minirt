/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inverse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:17:51 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/16 16:19:25 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

static void	fill_minor_matrix(double minor[3][3], t_matrix mat, int row, int col)
{
	int	i;
	int	j;
	int	mi;
	int	mj;

	mi = 0;
	i = -1;
	while (++i < 4)
	{
		if (i != row)
		{
			mj = 0;
			j = 0;
			while (j < 4)
			{
				if (j != col)
				{
					minor[mi][mj] = mat.m[i][j];
					mj++;
				}
				j++;
			}
			mi++;
		}
	}
}

static double	calculate_minor(t_matrix mat, int row, int col)
{
	double	minor[3][3];

	fill_minor_matrix(minor, mat, row, col);
	return (determinant3x3(minor));
}

// Calcul de la matrice cofacteur pour une matrice 4x4
static t_matrix	calculate_cofactor_matrix(t_matrix mat)
{
	t_matrix	cofactor;
	int			i;
	int			j;
	double		sign;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if ((i + j) % 2 == 0)
				sign = 1.0;
			else
				sign = -1.0;
			cofactor.m[i][j] = sign * calculate_minor(mat, i, j);
			j++;
		}
		i++;
	}
	return (cofactor);
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
		return (matrix_identity());
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