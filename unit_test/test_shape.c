#include <criterion/criterion.h>
#include "../include/graphics.h"
#include "../include/shape.h"
#include "../object/test_shape.h"

/*​ 	​Scenario​: The default transformation
​ 	  ​Given​ s ← test_shape()
​ 	  ​Then​ s.transform = identity_matrix
​ 	
​ 	​Scenario​: Assigning a transformation
​ 	  ​Given​ s ← test_shape()
​ 	  ​When​ set_transform(s, translation(2, 3, 4))
​ 	  ​Then​ s.transform = translation(2, 3, 4)     */

#include "../object/test_shape.h"

// // test test_shape
// Test(shape_tests, default_transformation) {
//     t_shape *s = test_shape();
//     t_matrix id = matrix_init_identity();
//     for (int i = 0; i < 4; ++i) {
//         for (int j = 0; j < 4; ++j) {
//             cr_assert_float_eq(s->transformation.m[i][j], id.m[i][j], 1e-6, "La transformation par défaut doit être la matrice identité.");
//         }
//     }
//     free(s);
// }

// // test set_shape_transform
// Test(shape_tests, assigning_transformation) {
//     t_shape *s = test_shape();
//     t_matrix transform = matrix_translation(2, 3, 4);
//     set_shape_transform(s, transform);
//     for (int i = 0; i < 4; ++i) {
//         for (int j = 0; j < 4; ++j) {
//             cr_assert_float_eq(s->transformation.m[i][j], transform.m[i][j], 1e-6, "La transformation assignée doit correspondre.");
//         }
//     }
//     free(s);
// }

// // test material default
// Test(shape_tests, default_material) {
//     t_shape *s = test_shape();
//     t_material m = s->material;
//     t_material default_material = material_create_default();
//     cr_assert_float_eq(m.ambient, default_material.ambient, 1e-6, "Le matériau par défaut ne correspond pas.");
//     free(s);
// }

// // test set_material 
// Test(shape_tests, assigning_material) {
//     t_shape *s = test_shape();
//     t_material m = material_create_default();
//     m.ambient = 1;
//     shape_set_material(s, m);
//     // Comparez s->material avec m.
//     cr_assert_float_eq(s->material.ambient, m.ambient, 1e-6, "L'ambient du matériau assigné doit correspondre.");
//     free(s);
// }

Test(shape_tests, normal_translated_shape)
{
    t_sphere *s = sphere_create();
    t_matrix transform = matrix_translation(0, 1, 0);
    t_object *obj = object_create_for_sphere(s);

    set_shape_transform(obj->shape, transform);
    t_tuple n = normal_at_shape(obj, point_create(0, 1.70711, -0.70711));
    cr_assert_float_eq(n.x, 0, 1e-5, "Normal X component is incorrect");
    cr_assert_float_eq(n.y, 0.70711, 1e-5, "Normal Y component is incorrect");
    cr_assert_float_eq(n.z, -0.70711, 1e-5, "Normal Z component is incorrect");

}

Test(shape_tests, normal_transformed_shape) {
    t_sphere *s = sphere_create();
    t_object *obj = object_create_for_sphere(s);
    double sqrt_2_over_2 = sqrt(2) / 2;

    t_matrix m = matrix_multiply(matrix_scaling(1, 0.5, 1), matrix_rotation_z(M_PI / 5));
    set_shape_transform(obj->shape, m);
    t_tuple n = normal_at_shape(obj, point_create(0, sqrt_2_over_2, -sqrt_2_over_2));

    cr_assert_float_eq(n.x, 0, 1e-5, "Normal X component is incorrect");
    cr_assert_float_eq(n.y, 0.97014, 1e-5, "Normal Y component is incorrect");
    cr_assert_float_eq(n.z, -0.24254, 1e-5, "Normal Z component is incorrect");
}
