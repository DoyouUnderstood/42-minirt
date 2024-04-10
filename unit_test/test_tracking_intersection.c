#include <criterion/criterion.h>
#include "../include/shape.h"

Test(intersection_tests, intersect_sets_object_on_the_intersection) 
{
    t_ray ray = {point_create(0, 0, -5), vector_create(0, 0, 1)};
    t_sphere *sphere = sphere_create();
    t_object *obj =  object_create_for_sphere(sphere);
    int count;
    t_intersection* xs = intersect(&ray, obj, &count);

    cr_expect_eq(count, 2, "Expected 2 intersections, but got %d", count);
    for (int i = 0; i < count; i++) {
        cr_expect(xs[i].obj == obj, "Expected object to be the sphere object");
    }
    free(sphere);
    free(xs);
}


Test(intersection_tests, encapsulates_t_and_object) {
    t_sphere *s = sphere_create();
    t_object *obj = object_create_for_sphere(s);

    int count;

    t_intersection* intersections = intersect(&(t_ray){.origin = point_create(0,0,-5), .direction = vector_create(0,0,1)}, obj, &count);
    
    if (count > 0) {
        cr_expect_float_eq(intersections[0].t, 4.0, 1e-6, "Expected t to be 4.0, was %f", intersections[0].t);
        cr_expect(intersections[0].obj == obj, "Intersection object does not match the given sphere object");
    } else {
        cr_expect_fail("No intersections found");
    }

    free(intersections);
}
