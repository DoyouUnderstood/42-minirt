/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:55:19 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/16 16:22:53 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "tuple.h"

# include <stdbool.h>

typedef struct s_matrix
{
	float	m[4][4];
}			t_matrix;

typedef struct s_shearing_params
{
	double	xy;
	double	xz;
	double	yx;
	double	yz;
	double	zx;
	double	zy;
}	t_shearing_params;

// ============ MATRIX OPERATION ================

t_matrix	matrix_create(float values[4][4]);
t_matrix	matrix_identity(void);
void		matrix_draw(t_matrix matrice);

// ============ MATRIX OPERATION ================

t_matrix	matrix_mult(t_matrix Ma, t_matrix Mb);
t_matrix	matrix_transpose(t_matrix mat);
t_tuple		matrix_mult_tuple(t_matrix mat, t_tuple tup);
t_matrix	matrix_inverse(t_matrix mat);

// ========= DETERMINANT =============

double		determinant3x3(double matrix[3][3]);
double		determinant4x4(t_matrix mat);

// ========== MATRIX TRANSFORM ===============

t_matrix	matrix_rotation_y(double angle);
t_matrix	matrix_rotation_z(double angle);
t_matrix	matrix_rotation_x(double angle);
t_matrix	matrix_shearing(t_shearing_params params);
t_matrix	matrix_scaling(double sx, double sy, double sz);
t_matrix	matrix_translation(double dx, double dy, double dz);

#endif