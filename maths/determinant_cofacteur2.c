/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determinant_cofacteur2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:25:07 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/15 17:29:03 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mathematique.h"
#include "maths.h"

// Calcul de la matrice cofacteur pour une matrice 4x4
t_matrix	calculate_cofactor_matrix(t_matrix mat)
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

void	matrix_submatrix4x4(t_matrix mat, double sub_matrix4x4[3][3],
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
