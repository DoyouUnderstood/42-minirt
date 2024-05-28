/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:00:28 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/28 10:40:01 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

#include <stdio.h>

t_matrix	matrix_create(float values[4][4])
{
	t_matrix	mat;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			mat.m[i][j] = values[i][j];
			j++;
		}
		i++;
	}
	return (mat);
}

t_matrix	matrix_identity(void)
{
	static t_matrix	identity
		= {.m = {{1.0, 0.0, 0.0, 0.0}, {0.0, 1.0, 0.0, 0.0},
	{0.0, 0.0, 1.0, 0.0}, {0.0, 0.0, 0.0, 1.0}}};

	return (identity);
}

// Fonction pour afficher une matrice 4x4
void	matrix_draw(t_matrix matrice)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			printf("%0.2f ", matrice.m[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
