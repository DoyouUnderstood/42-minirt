/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_determinant.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:15:15 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/16 16:17:08 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

static void	matrix_submatrix4x4(t_matrix mat, double sub_matrix4x4[3][3],
		int excluding_row, int excluding_col)
{
	int	i;
	int	di;
	int	j;
	int	dj;

	i = -1;
	di = 0;
	while (++i < 4)
	{
		if (i != excluding_row)
		{
			j = 0;
			dj = 0;
			while (j < 4)
			{
				if (j != excluding_col)
				{
					sub_matrix4x4[di][dj] = mat.m[i][j];
					dj++;
				}
				j++;
			}
			di++;
		}
	}
}

// calcul le determinant d'une Matrice 3x3
double	determinant3x3(double matrix[3][3])
{
	double	det;

	det = matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2]
			* matrix[2][1]) - matrix[0][1] * (matrix[1][0] * matrix[2][2]
			- matrix[1][2] * matrix[2][0]) + matrix[0][2] * (matrix[1][0]
			* matrix[2][1] - matrix[1][1] * matrix[2][0]);
	return (det);
}

// fonction pour determiner le determinant d'un matrice 4x4
double	determinant4x4(t_matrix mat)
{
	double	det;
	int		col;
	double	submatrix[3][3];
	double	minor;
	double	cofactor;

	col = 0;
	det = 0.0;
	while (col < 4)
	{
		matrix_submatrix4x4(mat, submatrix, 0, col);
		minor = determinant3x3(submatrix);
		if (col % 2 == 0)
		{
			cofactor = 1 * minor;
		}
		else
		{
			cofactor = -1 * minor;
		}
		det += mat.m[0][col] * cofactor;
		col++;
	}
	return (det);
}
