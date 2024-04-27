#ifndef MATHS_H
#define MATHS_H

#include "../include/mathematique.h"
#include "../include/types.h"
#include "../include/light.h"
#include "../include/pattern.h"
#include "../include/minilibx.h"

typedef struct s_mlx t_mlx;
// =========== RAY ============

t_ray ray_create(t_tuple origin, t_tuple direction);
t_ray   ray_transform(t_matrix mat, t_ray ray);
// void    ray_throw(t_mlx *mlx, t_sphere *sphere, t_light *light);
t_tuple t_point_position(const t_ray *ray, double t);
t_ray   ray_init(t_mlx *mlx, int x, int y, double projection_plane_z);


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