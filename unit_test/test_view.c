#include <criterion/criterion.h>
#include "../include/shape.h"
#include "../object/test_shape.h"

Test(view_transform_tests, default_orientation) 
{
    t_tuple from = point_create(0, 0, 0);
    t_tuple to = point_create(0, 0, -1);
    t_tuple up = vector_create(0, 1, 0);
    t_matrix t = view_transform(from, to, up);
    t_matrix expected = matrix_init_identity();
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cr_expect_float_eq(t.m[i][j], expected.m[i][j], 1e-5, "Default orientation should be identity matrix");
        }
    }
}

Test(view_transform_tests, looking_in_positive_z_direction) {
    t_tuple from = point_create(0, 0, 0);
    t_tuple to = point_create(0, 0, 1);
    t_tuple up = vector_create(0, 1, 0);
    t_matrix t = view_transform(from, to, up);
    t_matrix expected = matrix_scaling(-1, 1, -1);
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cr_expect_float_eq(t.m[i][j], expected.m[i][j], 1e-5, "View transform should be equivalent to scaling(-1, 1, -1)");
        }
    }
}

Test(view_transform_tests, moving_the_world) {
    t_tuple from = point_create(0, 0, 8);
    t_tuple to = point_create(0, 0, 0);
    t_tuple up = vector_create(0, 1, 0);
    t_matrix t = view_transform(from, to, up);
    t_matrix expected = matrix_translation(0, 0, -8);
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cr_expect_float_eq(t.m[i][j], expected.m[i][j], 1e-5, "View transform should translate the world by (0, 0, -8)");
        }
    }
}


Test(view_transform_tests, arbitrary_view_transformation) {
    t_tuple from = point_create(1, 3, 2);
    t_tuple to = point_create(4, -2, 8);
    t_tuple up = vector_create(1, 1, 0);
    t_matrix t = view_transform(from, to, up);

    float expected_values[4][4] = {
        {-0.50709,  0.50709,  0.67612, -2.36643},
        { 0.76772,  0.60609,  0.12122, -2.82843},
        {-0.35857,  0.59761, -0.71714,  0.00000},
        { 0.00000,  0.00000,  0.00000,  1.00000}
    };

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cr_expect_float_eq(t.m[i][j], expected_values[i][j], 1e-5, 
                "Element at (%d, %d) is incorrect: Expected %f, Got %f", i, j, expected_values[i][j], t.m[i][j]);
        }
    }
}