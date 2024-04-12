#include "../include/mathematique.h"

t_matrix matrix(float values[4][4]) 
{
    t_matrix mat;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            mat.m[i][j] = values[i][j];
        }
    }
    
    return (mat);
}

// Fonction qui réfléchit un point ou un vecteur par rapport à un axe spécifié.
t_tuple tuple_reflect(t_tuple point, char axis) 
{
    switch (axis) {
        case 'x':
            point.x = -point.x;
            break;
        case 'y':
            point.y = -point.y;
            break;
        case 'z':
            point.z = -point.z;
            break;
        default:
            printf("Axe invalide. Chois issez 'x', 'y', ou 'z'.\n");
    }
    return point;
}

// fonction qui crée une matrice de mise à l'échelle.
t_matrix matrix_scaling(double sx, double sy, double sz) 
{
    t_matrix matrix = matrix_init_identity();
    matrix.m[0][0] = sx;
    matrix.m[1][1] = sy;
    matrix.m[2][2] = sz;
    return matrix;
}

// fonction qui crée une matrice de rotation autour de l'axe z.
t_matrix matrix_rotation_z(double angle) 
{
    t_matrix matrix = matrix_init_identity();
    double cosTheta = cos(angle);
    double sinTheta = sin(angle);

    matrix.m[0][0] = cosTheta;
    matrix.m[0][1] = -sinTheta;
    matrix.m[1][0] = sinTheta;
    matrix.m[1][1] = cosTheta;

    return matrix;
}

// fonction qui crée une matrice de cisaillement.
t_matrix matrix_shearing(double xy, double xz, double yx, double yz, double zx, double zy) {
    t_matrix matrix = matrix_init_identity();

    matrix.m[0][1] = xy;
    matrix.m[0][2] = xz;
    matrix.m[1][0] = yx;
    matrix.m[1][2] = yz;
    matrix.m[2][0] = zx;
    matrix.m[2][1] = zy;

    return matrix;
}

// fonction qui crée une matrice de rotation autour de l'axe y.
t_matrix matrix_rotation_y(double angle) {
    t_matrix matrix = matrix_init_identity();
    double cosTheta = cos(angle);
    double sinTheta = sin(angle);

    matrix.m[0][0] = cosTheta;
    matrix.m[0][2] = sinTheta;
    matrix.m[2][0] = -sinTheta;
    matrix.m[2][2] = cosTheta;

    return matrix;
}

// fonction qui crée une matrice de rotation autour de l'axe x.
t_matrix matrix_rotation_x(double angle) {
    t_matrix matrix = matrix_init_identity();
    double cosTheta = cos(angle);
    double sinTheta = sin(angle);

    matrix.m[1][1] = cosTheta;
    matrix.m[1][2] = -sinTheta;
    matrix.m[2][1] = sinTheta;
    matrix.m[2][2] = cosTheta;

    return matrix;
}

// Fonction pour créer une matrice de translation
t_matrix matrix_translation(double dx, double dy, double dz) {
    t_matrix mat = {{{1, 0, 0, dx},
                       {0, 1, 0, dy},
                       {0, 0, 1, dz},
                       {0, 0, 0, 1}}};
    return mat;
}

#include "../object/test_shape.h"

void set_transform(t_object *object, t_matrix transform) {
    if (object && object->shape) {
        object->shape->transformation = transform;
    }
}
