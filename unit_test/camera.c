#include <criterion/criterion.h>
#include "../include/shape.h"
#include <math.h>

#define M_PI       3.14159265358979323846

Test(camera_tests, pixel_size_for_horizontal_canvas) {
    t_camera c = camera_create(200, 125, M_PI / 2);
    cr_expect_float_eq(c.pixel_size, 0.01, 1e-5, "Pixel size should be 0.01 for horizontal canvas.");
}

Test(camera_tests, pixel_size_for_vertical_canvas) {
    t_camera c = camera_create(125, 200, M_PI / 2);
    cr_expect_float_eq(c.pixel_size, 0.01, 1e-5, "Pixel size should be 0.01 for vertical canvas.");
}

Test(ray_for_pixel_tests, ray_through_center_of_canvas) {
    t_camera c = camera_create(201, 101, M_PI / 2);
    t_ray *r = ray_for_pixel(&c, 100, 50);
    cr_expect(tuple_eq(r->origin, point_create(0, 0, 0)), "Ray origin should be at the camera's origin.");
    cr_expect(tuple_eq(r->direction, vector_create(0, 0, -1)), "Ray direction should be towards negative z.");
}

Test(ray_for_pixel_tests, ray_through_corner_of_canvas) 
{
    t_camera c = camera_create(201, 101, M_PI / 2);
    t_ray *r = ray_for_pixel(&c, 0, 0);
    cr_expect(tuple_eq(r->origin, point_create(0, 0, 0)), "Ray origin should be at the camera's origin.");
    cr_expect(tuple_eq(r->direction, vector_create(0.665186, 0.332593, -0.668512)), "Ray direction is incorrect.");
}

Test(ray_for_pixel_tests, ray_with_transformed_camera) 
{
    t_camera c = camera_create(201, 101, M_PI / 2);
    t_matrix rotation = matrix_rotation_y(M_PI / 4);
    t_matrix translation = matrix_translation(0, -2, 5);
    c.transform = matrix_multiply(rotation, translation);

    t_ray *r = ray_for_pixel(&c, 100, 50);
    cr_expect(tuple_eq(r->origin, point_create(0, 2, -5)), "Ray origin is incorrect after camera transformation.");
    cr_expect(tuple_eq(r->direction, vector_create(sqrt(2)/2, 0, -sqrt(2)/2)), "Ray direction is incorrect after camera transformation.");
}