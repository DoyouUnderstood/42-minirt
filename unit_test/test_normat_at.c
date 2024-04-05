#include <criterion/criterion.h>
#include <math.h>
#include "../include/mathematique.h"
#include "../include/shape.h"


t_tuple		point_create(double x, double y, double z);
t_tuple normal_at(const t_sphere* sphere, t_tuple world_point);

Test(sphere_normal_tests, normal_on_sphere_at_point_on_x_axis) 
{
    t_sphere *s = sphere_create();
    t_tuple point_point = point_create(1, 0, 0);
    t_tuple expected = vector_create(1, 0, 0);
    t_tuple result = normal_at(s, point_point);
    cr_assert_float_eq(result.x, expected.x, 1e-6, "Normal X component is incorrect");
    cr_assert_float_eq(result.y, expected.y, 1e-6, "Normal Y component is incorrect");
    cr_assert_float_eq(result.z, expected.z, 1e-6, "Normal Z component is incorrect");
}

Test(sphere_normal_tests, normal_on_sphere_at_point_on_y_axis) 
{
    t_sphere *s = sphere_create();
    t_tuple point_point = point_create(0, 1, 0);
    t_tuple expected = vector_create(0, 1, 0);
    t_tuple result = normal_at(s, point_point);
    cr_assert_float_eq(result.x, expected.x, 1e-6, "Normal X component is incorrect");
    cr_assert_float_eq(result.y, expected.y, 1e-6, "Normal Y component is incorrect");
    cr_assert_float_eq(result.z, expected.z, 1e-6, "Normal Z component is incorrect");
}

Test(sphere_normal_tests, normal_on_sphere_at_point_on_z_axis) 
{
    t_sphere *s = sphere_create();
    t_tuple point_point = point_create(0, 0, 1);
    t_tuple expected = vector_create(0, 0, 1);
    t_tuple result = normal_at(s, point_point);
    cr_assert_float_eq(result.x, expected.x, 1e-6, "Normal X component is incorrect");
    cr_assert_float_eq(result.y, expected.y, 1e-6, "Normal Y component is incorrect");
    cr_assert_float_eq(result.z, expected.z, 1e-6, "Normal Z component is incorrect");
}

Test(sphere_normal_tests, normal_on_sphere_at_nonaxial_point) 
{
    t_sphere *s = sphere_create();
    double sqrt_3_over_3 = sqrt(3.0) / 3.0;
    t_tuple point_point = point_create(sqrt_3_over_3, sqrt_3_over_3, sqrt_3_over_3);
    t_tuple expected = vector_create(sqrt_3_over_3, sqrt_3_over_3, sqrt_3_over_3);
    t_tuple result = normal_at(s, point_point);
    cr_assert_float_eq(result.x, expected.x, 1e-6, "Normal X component is incorrect");
    cr_assert_float_eq(result.y, expected.y, 1e-6, "Normal Y component is incorrect");
    cr_assert_float_eq(result.z, expected.z, 1e-6, "Normal Z component is incorrect");
}

