#include <criterion/criterion.h>
#include "../include/shape.h"
#include "../object/test_shape.h"

// Test pour "Le hit, lorsque toutes les intersections ont un t positif"
Test(hit_tests, all_positive_t) 
{
    t_sphere* s = sphere_create();
    t_object* obj = object_create_for_sphere(s);
    t_intersection i1 = intersection_create(1, obj);
    t_intersection i2 = intersection_create(2, obj);
    t_intersection xs[] = {i1, i2};
    t_intersection* hit_result = hit(xs, 2);
    cr_assert_not_null(hit_result, "Le hit ne devrait pas être NULL");
    cr_assert(hit_result->t == i1.t, "Le hit devrait avoir la même valeur t que i1");
    cr_assert(hit_result->obj == i1.obj, "L'objet du hit devrait être le même que celui de i1");

    free(s);
    free(obj);
}


Test(hit_tests, some_negative_t) {
    t_sphere* s = sphere_create();
    t_object* obj = object_create_for_sphere(s);
    t_intersection i1 = intersection_create(-1, obj); 
    t_intersection i2 = intersection_create(1, obj);
    t_intersection xs[] = {i1, i2};
    t_intersection* hit_result = hit(xs, 2);
    cr_assert_not_null(hit_result, "Hit ne devrait pas être NULL");
    cr_assert_float_eq(hit_result->t, i2.t, 1e-6, "Le hit devrait avoir la même valeur t que i2");
}


// Test pour "Le hit est toujours l'intersection positive la plus basse"
Test(hit_tests, lowest_nonnegative_intersection) {
    t_sphere* s = sphere_create();
    t_object* obj = object_create_for_sphere(s);
    t_intersection i1 = intersection_create(5, obj);
    t_intersection i2 = intersection_create(7, obj);
    t_intersection i3 = intersection_create(-3, obj);
    t_intersection i4 = intersection_create(2, obj);
    t_intersection xs[] = {i1, i2, i3, i4};
    t_intersection* hit_result = hit(xs, 4);
    cr_assert_not_null(hit_result, "Hit ne devrait pas être NULL");
    cr_assert_float_eq(hit_result->t, i4.t, 1e-6, "Le hit devrait être i4");
}

Test(hit_tests, no_positive_intersection) {
    t_sphere* s = sphere_create();
    t_object* obj = object_create_for_sphere(s);
    t_intersection i1 = intersection_create(-2, obj);
    t_intersection i2 = intersection_create(-1, obj);
    t_intersection xs[] = {i1, i2};
    t_intersection* hit_result = hit(xs, 2);
    cr_assert_null(hit_result, "Il ne devrait y avoir aucun hit, car toutes les intersections ont un 't' négatif.");
    
    free(s);
    free(obj);
}
