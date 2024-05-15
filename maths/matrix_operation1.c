/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operation1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:25:17 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/15 17:32:14 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mathematique.h"
#include "maths.h"

t_matrix	matrix_init_identity(void)
{
	t_matrix	matrice;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i == j)
				matrice.m[i][j] = 1.0f;
			else
				matrice.m[i][j] = 0.0f;
			j++;
		}
		i++;
	}
	return (matrice);
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

// Fonction pour determiner si une matrice est une matrice identite
bool	matrix_is_identity(t_matrix mat)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if ((i == j && mat.m[i][j] != 1.0) || (i != j
					&& mat.m[i][j] != 0.0))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

// Fonction pour multiplier deux matrices 4x4
t_matrix	matrix_multiply(t_matrix Ma, t_matrix Mb)
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

// Fonction qui determine si ce sont les memes matrices
int	is_same_matrice(t_matrix Ma, t_matrix Mb)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (Ma.m[i][j] != Mb.m[i][j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
