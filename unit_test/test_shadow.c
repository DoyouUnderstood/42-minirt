#include <criterion/criterion.h>
#include "../include/graphics.h"
#include "../include/shape.h"
#include "../object/test_shape.h"

Test(shadow_tests, no_shadow_when_nothing_collinear_with_point_and_light) {
    t_world *world = world_default();
    t_tuple point = point_create(0, 10, 0);

    cr_assert_eq(is_shadowed(world, point), false, "Point should not be in shadow");
}

Test(shadow_tests, shadow_when_object_between_point_and_light) {
    t_world *world = world_default();
    t_tuple point = point_create(10, -10, 10);

    cr_assert_eq(is_shadowed(world, point), true, "Point should be in shadow");
}

Test(shadow_tests, no_shadow_when_object_behind_light) {
    t_world *world = world_default();
    t_tuple point = point_create(-20, 20, -20);

    cr_assert_eq(is_shadowed(world, point), false, "Point should not be in shadow");
}

Test(shadow_tests, no_shadow_when_object_behind_point) {
    t_world *world = world_default();
    t_tuple point = point_create(-2, 2, -2);

    cr_assert_eq(is_shadowed(world, point), false, "Point should not be in shadow");
}
