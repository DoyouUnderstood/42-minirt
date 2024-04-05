#include <criterion/criterion.h>
#include "../include/shape.h"

Test(ray_tracing, intersect_world_with_a_ray) {
    t_world *w = world_default();
    
    t_ray *r = ray_create(point_create(0, 0, -5), vector_create(0, 0, 1));
    
    int count = 0;
    t_intersection *xs = intersect_world(w, r, &count);
    
    cr_assert_eq(count, 4, "Le nombre d'intersections devrait être %d, mais était %d", 4, count);
    
    cr_assert_float_eq(xs[0].t, 4.0, 1e-6, "Le premier point d'intersection devrait être à t=%f, mais était à t=%f", 4.0, xs[0].t);
    
    cr_assert_float_eq(xs[1].t, 4.5, 1e-6, "Le deuxième point d'intersection devrait être à t=%f, mais était à t=%f", 4.5, xs[1].t);
    
    cr_assert_float_eq(xs[2].t, 5.5, 1e-6, "Le troisième point d'intersection devrait être à t=%f, mais était à t=%f", 5.5, xs[2].t);
    
    cr_assert_float_eq(xs[3].t, 6.0, 1e-6, "Le quatrième point d'intersection devrait être à t=%f, mais était à t=%f", 6.0, xs[3].t);

    if (xs != NULL) {
        free(xs);
    }
}
