#include "../include/mathematique.h"
#include "maths.h"

// fonction pour determiner le determinant d'un matrice 4x4
double determinant4x4(t_matrix mat) 
{
    double det;
    int col;

    col = 0;
    det = 0.0;
    while (col < 4) 
    {
        double subMatrice4x4[3][3];
        matrix_submatrix4x4(mat, subMatrice4x4, 0, col);
        double minor = determinant3x3(subMatrice4x4);
        double cofactor = (col % 2 == 0 ? 1 : -1) * minor;
        det += mat.m[0][col] * cofactor;
        col++;
    }
    return (det);
}

// calcul le determinant d'une Matrice 3x3
double determinant3x3(double matrix[3][3]) 
{
    double det = matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
                 matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
                 matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
    return (det);
}

// fonction pour calculer le determinant d'un matrice 2x2
double determinant2x2(double Matrice4x4[2][2]) 
{
    return (Matrice4x4[0][0] * Matrice4x4[1][1] - Matrice4x4[0][1] * Matrice4x4[1][0]);
}


// Calcul du mineur d'une matrice 4x4
double calculate_minor(t_matrix mat, int row, int col)
{
    double minor[3][3];
    double det;
    int i = 0;
    int mi = 0;

    while (i < 4)
    {
        if (i != row)
        {
            int j = 0;
            int mj = 0;
            while (j < 4)
            {
                if (j != col)
                {
                    minor[mi][mj] = mat.m[i][j];
                    mj++;
                }
                j++;
            }
            mi++;
        }
        i++;
    }
    det = determinant3x3(minor);
    return (det);
}

// Calcul de la matrice cofacteur pour une matrice 4x4
t_matrix calculate_cofactor_matrix(t_matrix mat)
{
    t_matrix cofactor;
    int i = 0;

    while (i < 4)
    {
        int j = 0;
        while (j < 4)
        {
            double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
            cofactor.m[i][j] = sign * calculate_minor(mat, i, j);
            j++;
        }
        i++;
    }
    return cofactor;
}

// Extraction d'une sous-matrice 3x3 d'une matrice 4x4 en excluant une ligne et une colonne spécifiques
void matrix_submatrix4x4(t_matrix mat, double sub_matrix4x4[3][3], int excluding_row, int excluding_col)
{
    int i = 0;
    int di = 0;

    while (i < 4)
    {
        if (i != excluding_row)
        {
            int j = 0;
            int dj = 0;
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
        i++;
    }
}

