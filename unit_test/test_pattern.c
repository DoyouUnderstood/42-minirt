#include <criterion/criterion.h>
#include "../include/shape.h"
#include "../object/test_shape.h"

#include <criterion/criterion.h>
#include <math.h>

Test(pattern_tests, stripe_pattern_creates_a_stripe_pattern_with_two_colors) {
    t_color white = (t_color){1, 1, 1};
    t_color black = (t_color){0, 0, 0};
    t_pattern pattern = stripe_pattern_create(white, black);

    cr_expect(color_eq(pattern.color_a, white), "The first color should be white");
    cr_expect(color_eq(pattern.color_b, black), "The second color should be black");
}

Test(pattern_tests, stripe_pattern_is_constant_in_y) {
    t_pattern pattern = stripe_pattern_create((t_color){1, 1, 1}, (t_color){0, 0, 0});

    cr_expect(color_eq(stripe_at(pattern, point_create(0, 0, 0)), color_create(1, 1, 1)), "Stripe at y=0 should be white");
    cr_expect(color_eq(stripe_at(pattern, point_create(0, 1, 0)), color_create(1, 1, 1)), "Stripe at y=1 should be white");
    cr_expect(color_eq(stripe_at(pattern, point_create(0, 2, 0)), color_create(1, 1, 1)), "Stripe at y=2 should be white");
}

Test(pattern_tests, stripe_pattern_is_constant_in_z) {
    t_pattern pattern = stripe_pattern_create((t_color){1, 1, 1}, (t_color){0, 0, 0});

    cr_expect(color_eq(stripe_at(pattern, point_create(0, 0, 0)), color_create(1, 1, 1)), "Stripe at z=0 should be white");
    cr_expect(color_eq(stripe_at(pattern, point_create(0, 0, 1)), color_create(1, 1, 1)), "Stripe at z=1 should be white");
    cr_expect(color_eq(stripe_at(pattern, point_create(0, 0, 2)), color_create(1, 1, 1)), "Stripe at z=2 should be white");
}

Test(pattern_tests, stripe_pattern_alternates_in_x) {
    t_pattern pattern = stripe_pattern_create(color_create(1, 1, 1), color_create(0, 0, 0));

    cr_expect(color_eq(stripe_at(pattern, point_create(0, 0, 0)), color_create(1, 1, 1)), "Stripe at x=0 should be white");
    cr_expect(color_eq(stripe_at(pattern, point_create(0.9, 0, 0)), color_create(1, 1, 1)), "Stripe at x=0.9 should be white");
    cr_expect(color_eq(stripe_at(pattern, point_create(1, 0, 0)), color_create(0, 0, 0)), "Stripe at x=1 should be black");
    cr_expect(color_eq(stripe_at(pattern, point_create(-0.1, 0, 0)), color_create(0, 0, 0)), "Stripe at x=-0.1 should be black");
    cr_expect(color_eq(stripe_at(pattern, point_create(-1, 0, 0)), color_create(0, 0, 0)), "Stripe at x=-1 should be black");
    cr_expect(color_eq(stripe_at(pattern, point_create(-1.1, 0, 0)), color_create(1, 1, 1)), "Stripe at x=-1.1 should be white");
}

Test(light_with_pattern, lighting_with_a_pattern_applied) 
{
    t_pattern pattern = stripe_pattern_create(color_create(1, 1, 1), color_create(0, 0, 0));
    t_material m = material_create_default();
    m.pattern = pattern;
    m.ambient = 1;
    m.diffuse = 0;
    m.specular = 0;

    t_tuple eyev = vector_create(0, 0, -1);
    t_tuple normalv = vector_create(0, 0, -1);

    t_light *light = light_create(color_create(1, 1, 1), point_create(0, 0, -10));

    t_tuple point1 = point_create(0.9, 0, 0);
    t_tuple point2 = point_create(1.1, 0, 0);

    t_color c1 = lighting(&m, light, &point1, &eyev, &normalv, false);
    t_color c2 = lighting(&m, light, &point2, &eyev, &normalv, false);

    // Comparaison des couleurs attendues.
    t_color expected_white = color_create(1, 1, 1);
    t_color expected_black = color_create(0, 0, 0);

    cr_expect(color_eq(c1, expected_white), "When point is at (0.9, 0, 0) color should be white.");
    cr_expect(color_eq(c2, expected_black), "When point is at (1.1, 0, 0) color should be black.");
}

#include <criterion/criterion.h>

Test(plane_tests, normal_of_plane_is_constant) {
    t_plane *plane = plane_create();
    t_object *plane_obj = object_create_for_plane(plane);
    t_tuple point_on_plane;

    point_on_plane = point_create(0, 0, 0);
    cr_expect_eq(tuple_eq(plane_local_normal_at(plane_obj->shape, point_on_plane), vector_create(0, 1, 0)),
                 true, "The normal at the origin should be (0, 1, 0)");

    point_on_plane = point_create(10, 0, -10);
    cr_expect_eq(tuple_eq(plane_local_normal_at(plane_obj->shape, point_on_plane), vector_create(0, 1, 0)),
                 true, "The normal at (10, 0, -10) should be (0, 1, 0)");

    point_on_plane = point_create(-5, 0, 150);
    cr_expect_eq(tuple_eq(plane_local_normal_at(plane_obj->shape, point_on_plane), vector_create(0, 1, 0)),
                 true, "The normal at (-5, 0, 150) should be (0, 1, 0)");

    free(plane);
    free(plane_obj);
}

Test(plane_tests, intersect_with_ray_parallel_to_plane12) {
    t_plane *plane = plane_create();
    t_object *plane_obj = object_create_for_plane(plane);
    t_ray ray = ray_create(point_create(0, 10, 0), vector_create(0, 0, 1));
    int count = 0;
    t_intersection *intersections = plane_obj->shape->local_intersect(plane_obj, &ray, &count);

    cr_expect_null(intersections, "Expected no intersections with a parallel ray");
    cr_expect_eq(count, 0, "Intersection count should be zero");

    free(plane);
    free(plane_obj);
}

Test(plane_tests, intersect_with_coplanar_ray2) {
    t_plane *plane = plane_create();
    t_object *plane_obj = object_create_for_plane(plane);
    t_ray ray = ray_create(point_create(0, 0, 0), vector_create(0, 0, 1));
    int count = 0;
    t_intersection *intersections = plane_local_intersect(plane_obj, &ray, &count);

    cr_expect_null(intersections, "Expected no intersections with a coplanar ray");
    cr_expect_eq(count, 0, "Intersection count should be zero");

    free(plane);
    free(plane_obj);
}

Test(pattern_tests, Stripes_with_object_transformation) {
    t_sphere *sphere = sphere_create();
    t_object *object = object_create_for_sphere(sphere);    set_transform(object, matrix_scaling(2, 2, 2));
    t_pattern pattern = stripe_pattern_create(color_create(1, 1, 1), color_create(0, 0, 0));
    t_color c = stripe_at_object(pattern, object, point_create(1.5, 0, 0));
    cr_expect(color_eq(c, color_create(1, 1, 1)), "Expected color to be white");
    free(object);
}


Test(pattern_tests, Stripes_with_pattern_transformation) {
    t_sphere *sphere = sphere_create();
    t_object *object = object_create_for_sphere(sphere);    t_pattern pattern = stripe_pattern_create(color_create(1, 1, 1), color_create(0, 0, 0));
    set_pattern_transform(&pattern, matrix_scaling(2, 2, 2));
    t_color c = stripe_at_object(pattern, object, point_create(1.5, 0, 0));
    cr_expect(color_eq(c, color_create(1, 1, 1)), "Expected color to be white");
    free(object);
}

Test(pattern_tests, Stripes_with_both_object_and_pattern_transformation) {
    t_sphere *sphere = sphere_create();
    t_object *object = object_create_for_sphere(sphere);
    set_transform(object, matrix_scaling(2, 2, 2));
    t_pattern pattern = stripe_pattern_create(color_create(1, 1, 1), color_create(0, 0, 0));
    set_pattern_transform(&pattern, matrix_translation(0.5, 0, 0));
    t_color c = stripe_at_object(pattern, object, point_create(2.5, 0, 0));
    cr_expect(color_eq(c, color_create(1, 1, 1)), "Expected color to be white");
    free(object);
}
