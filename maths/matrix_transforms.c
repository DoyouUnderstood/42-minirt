#include "../include/mathematique.h"
#include "maths.h"

t_matrix	matrix(float values[4][4])
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

t_tuple	tuple_reflect(t_tuple point, char axis)
{
	if (axis == 'x')
	{
		point.x = -point.x;
	}
	else if (axis == 'y')
	{
		point.y = -point.y;
	}
	else if (axis == 'z')
	{
		point.z = -point.z;
	}
	else
	{
		printf("Invalid axis. Choose 'x', 'y', or 'z'.\n");
	}
	return (point);
}

// fonction qui crée une matrice de mise à l'échelle.
t_matrix	matrix_scaling(double sx, double sy, double sz)
{
	t_matrix	matrix;

	matrix = matrix_init_identity();
	matrix.m[0][0] = sx;
	matrix.m[1][1] = sy;
	matrix.m[2][2] = sz;
	return (matrix);
}

// fonction qui crée une matrice de rotation autour de l'axe z.
t_matrix	matrix_rotation_z(double angle)
{
	t_matrix	matrix;
	double		costheta;
	double		sintheta;

	matrix = matrix_init_identity();
	costheta = cos(angle);
	sintheta = sin(angle);
	matrix.m[0][0] = costheta;
	matrix.m[0][1] = -sintheta;
	matrix.m[1][0] = sintheta;
	matrix.m[1][1] = costheta;
	return (matrix);
}

t_matrix	matrix_shearing(t_shearing_params params)
{
	t_matrix	matrix;

	matrix = matrix_init_identity();
	matrix.m[0][1] = params.xy;
	matrix.m[0][2] = params.xz;
	matrix.m[1][0] = params.yx;
	matrix.m[1][2] = params.yz;
	matrix.m[2][0] = params.zx;
	matrix.m[2][1] = params.zy;
	return (matrix);
}

// fonction qui crée une matrice de rotation autour de l'axe y.
t_matrix	matrix_rotation_y(double angle)
{
	t_matrix	matrix;
	double		costheta;
	double		sintheta;

	matrix = matrix_init_identity();
	costheta = cos(angle);
	sintheta = sin(angle);
	matrix.m[0][0] = costheta;
	matrix.m[0][2] = sintheta;
	matrix.m[2][0] = -sintheta;
	matrix.m[2][2] = costheta;
	return (matrix);
}

// fonction qui crée une matrice de rotation autour de l'axe x.
t_matrix	matrix_rotation_x(double angle)
{
	t_matrix	matrix;
	double		costheta;
	double		sintheta;

	matrix = matrix_init_identity();
	costheta = cos(angle);
	sintheta = sin(angle);
	matrix.m[1][1] = costheta;
	matrix.m[1][2] = -sintheta;
	matrix.m[2][1] = sintheta;
	matrix.m[2][2] = costheta;
	return (matrix);
}

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

void	set_transform(t_object *object, t_matrix transform)
{
	if (object && object->shape)
	{
		object->shape->transformation = transform;
	}
}
