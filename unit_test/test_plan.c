#include "../include/shape.h"
#include "../object/test_shape.h"

Test(plane_tests, normal_of_plane_is_constant_everywhere) {
    t_plane *p = plane_create();
    t_object *obj = object_create_for_plane(p);
    t_tuple n1 = obj->shape->local_normal_at(obj->shape, point_create(0, 0, 0));
    t_tuple n2 = obj->shape->local_normal_at(obj->shape, point_create(10, 0, -10));
    t_tuple n3 = obj->shape->local_normal_at(obj->shape, point_create(-5, 0, 150));

    t_tuple expected_normal = vector_create(0, 1, 0);

    cr_expect(tuple_eq(n1, expected_normal), "Normal at (0, 0, 0) is incorrect");
    cr_expect(tuple_eq(n2, expected_normal), "Normal at (10, 0, -10) is incorrect");
    cr_expect(tuple_eq(n3, expected_normal), "Normal at (-5, 0, 150) is incorrect");
}

Test(plane_tests, intersect_with_ray_parallel_to_plane) 
{
    t_plane *p = plane_create();
    t_object *obj = object_create_for_plane(p);
    t_ray r = ray_create(point_create(0, 10, 0), vector_create(0, 0, 1));
    int count;
    t_intersection* xs = obj->shape->local_intersect(obj, &r, &count);
    (void)xs;
    cr_expect_eq(count, 0, "Expected no intersections, got %d", count);
}

Test(plane_tests, intersect_with_coplanar_ray) 
{
    t_plane *p = plane_create();
    t_object *obj = object_create_for_plane(p);
    t_ray r = ray_create(point_create(0, 0, 0), vector_create(0, 0, 1));
    int count;
    t_intersection* xs = obj->shape->local_intersect(obj, &r, &count);
    (void)xs;
    cr_expect_eq(count, 0, "Expected no intersections, got %d", count);
}

Test(plane_tests, ray_intersects_plane_from_above) 
{
    t_plane *p = plane_create();
    t_object *obj = object_create_for_plane(p);
    t_ray r = ray_create(point_create(0, 1, 0), vector_create(0, -1, 0));
    int count;
    t_intersection* xs = obj->shape->local_intersect(obj, &r, &count);

    cr_expect_eq(count, 1, "Expected 1 intersection, got %d", count);
    cr_expect_eq(xs[0].t, 1, "Intersection at t=1 expected, got t=%f", xs[0].t);
    cr_expect(xs[0].obj == obj, "Intersection object should be the plane");
}

Test(plane_tests, ray_intersects_plane_from_below) {
    t_plane *p = plane_create();
    t_object *obj = object_create_for_plane(p);
    t_ray r = ray_create(point_create(0, -1, 0), vector_create(0, 1, 0));
    int count;
    t_intersection* xs = obj->shape->local_intersect(obj, &r, &count);

    cr_expect_eq(count, 1, "Expected 1 intersection, got %d", count);
    cr_expect_eq(xs[0].t, 1, "Intersection at t=1 expected, got t=%f", xs[0].t);
    cr_expect(xs[0].obj == obj, "Intersection object should be the plane");
}

