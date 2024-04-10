#ifndef MATHEMATIQUE_H
#define MATHEMATIQUE_H

// un tuple avec w = 0 est un vecteur 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

// Definition d' une précision standard pour la comparaison des tuples.
#define TUPLE_EPSILON 1e-6

typedef struct s_sphere t_sphere;

typedef struct s_tuple
{
    double x;
    double y;
    double z;
    double w;
} t_tuple;

typedef struct s_matrix
{
    float m[4][4];
} t_matrix;


// ============ TUPLE =============

t_tuple     tuple_subtract(t_tuple a, t_tuple b);
bool        tuple_eq(t_tuple a, t_tuple b);
t_tuple		tuple_scale(t_tuple point, double sx, double sy, double sz);
t_tuple		tuple_reflect(t_tuple point, char axis);
double      tuple_magnitude(const t_tuple *t);
t_tuple     tuple_add(t_tuple a, t_tuple b);

// ============ MATRIX OPERATION ================

t_matrix	matrix_init_identity();
t_matrix 	matrix_multiply(t_matrix Ma, t_matrix Mb);
t_matrix 	matrix_transpose(t_matrix mat);
t_matrix 	matrix_inverse(t_matrix mat);
void		matrix_draw(t_matrix matrice);
t_tuple 	matrix_multiply_by_tuple(t_matrix mat, t_tuple tup);
void 		matrix_submatrix4x4(t_matrix mat, double sub_matrix[3][3], int excluding_row, int excluding_col);
int 		is_same_matrice(t_matrix Ma, t_matrix Mb);

// ========= DETERMINANT COFACTEUR =============

double		determinant4x4(t_matrix mat);
double 		determinant3x3(double matrix[3][3]);
double 		determinant2x2(double matrix[2][2]);
double 		calculate_minor(t_matrix mat, int row, int col);
t_matrix 	calculate_cofactor_matrix(t_matrix mat);

// ========== MATRIX TRANSFORM ===============

t_matrix    matrix(float values[4][4]);
t_matrix	matrix_rotation_y(double angle);
t_matrix	matrix_rotation_z(double angle);
t_matrix	matrix_rotation_x(double angle);
t_matrix	matrix_shearing(double xy, double xz, double yx, double yz, double zx, double zy);
t_matrix	matrix_scaling(double sx, double sy, double sz);
t_matrix	matrix_translation(double dx, double dy, double dz);
bool        matrix_is_identity(t_matrix mat);

// ============== POINT ===============

t_tuple     point_sub(t_tuple point, t_tuple point2);
t_tuple		point_create(double x, double y, double z);
t_tuple		point_add_vector(t_tuple point, t_tuple vect);
t_tuple		point_multiply(t_tuple a, double scalar);
t_tuple		point_sub_vector(t_tuple point, t_tuple vect);

// ============== VECTEUR ===============

t_tuple		vector_create(double x, double y, double z);
t_tuple		vector_normalize(t_tuple a);
t_tuple     vector_negate(t_tuple v);
t_tuple		vector_add(t_tuple v1, t_tuple v2);
t_tuple		vector_scale(t_tuple v, double scalar);
double		vector_dot(t_tuple a, t_tuple b);
t_tuple		vector_multiply(t_tuple a, double scalar);
t_tuple     vector_cross(t_tuple a, t_tuple b);

// ============== NORMAL ===============

t_tuple reflect(t_tuple incident, t_tuple normal);

#endif