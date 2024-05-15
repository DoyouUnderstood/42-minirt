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
