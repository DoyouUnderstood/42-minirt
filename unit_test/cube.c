// tests/cube_tests.c
#include <criterion/criterion.h>
#include "../include/object.h"
#include "../include/shape.h"

Test(object_tests, cube_intersection) {
    t_object* cube = create_cube();
    t_ray ray = { {0, 0, -5, 1}, {0, 0, 1, 0} };  // Rayon pointant vers le cube
    int count;

    t_intersection* intersections = cube->shape->local_intersect(cube, &ray, &count);
    cr_assert_eq(count, 2, "Expected 2 intersections, got %d", count);
    if (count == 2) {
        cr_assert_float_eq(intersections[0].t, 4.0, 0.00001, "First intersection t should be 4.0");
        cr_assert_float_eq(intersections[1].t, 6.0, 0.00001, "Second intersection t should be 6.0");
    }

    free(intersections);
    free(cube->obj);
    free(cube->shape);
    free(cube);
}

Test(object_tests, cube_normal_at) {
    t_object* cube = create_cube();
    t_tuple point = {1, 0.5, -0.8, 1};  // Un point sur la face +x du cube
    t_tuple normal = cube->shape->local_normal_at(cube->shape, point);

    cr_assert_eq(normal.x, 1, "Normal x should be 1");
    cr_assert_eq(normal.y, 0, "Normal y should be 0");
    cr_assert_eq(normal.z, 0, "Normal z should be 0");

    free(cube->obj);
    free(cube->shape);
    free(cube);
}
