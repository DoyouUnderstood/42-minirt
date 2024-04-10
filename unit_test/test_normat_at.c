#include <criterion/criterion.h>
#include <math.h>
#include "../include/mathematique.h"
#include "../include/shape.h"
#include "../object/test_shape.h"

t_tuple		point_create(double x, double y, double z);

Test(sphere_normal_tests, normal_on_sphere_at_point_on_x_axis) 
{
    // Création d'une sphère.
    t_sphere *s = sphere_create();
    // Définir un point sur l'axe X de la sphère.
    t_tuple point_on_sphere = point_create(1, 0, 0);
    t_object *obj = object_create_for_sphere(s);
    // Appeler la fonction de calcul de la normale sur ce point.
    // Supposons que la sphère est centrée à l'origine et que sa transformation est la matrice identité.
    t_tuple normal_at_point = obj->shape->local_normal_at(obj->shape, point_on_sphere);
    
    // Le vecteur normal attendu en ce point.
    t_tuple expected = vector_create(1, 0, 0);
    
    // Vérifier que les composantes du vecteur normal calculé correspondent au vecteur attendu.
    cr_assert_float_eq(normal_at_point.x, expected.x, 1e-6, "Normal X component is incorrect");
    cr_assert_float_eq(normal_at_point.y, expected.y, 1e-6, "Normal Y component is incorrect");
    cr_assert_float_eq(normal_at_point.z, expected.z, 1e-6, "Normal Z component is incorrect");
}


Test(sphere_normal_tests, normal_on_sphere_at_point_on_y_axis) 
{
    t_sphere *s = sphere_create();
    t_tuple point_point = point_create(0, 1, 0);
    t_tuple expected = vector_create(0, 1, 0);
    t_object *obj = object_create_for_sphere(s);
    t_tuple result = obj->shape->local_normal_at(obj->shape, point_point);
    cr_assert_float_eq(result.x, expected.x, 1e-6, "Normal X component is incorrect");
    cr_assert_float_eq(result.y, expected.y, 1e-6, "Normal Y component is incorrect");
    cr_assert_float_eq(result.z, expected.z, 1e-6, "Normal Z component is incorrect");
}

Test(sphere_normal_tests, normal_on_sphere_at_point_on_z_axis) 
{
    t_sphere *s = sphere_create();
    t_tuple point_point = point_create(0, 0, 1);
    t_tuple expected = vector_create(0, 0, 1);
    t_object *obj = object_create_for_sphere(s);
    t_tuple result = obj->shape->local_normal_at(obj->shape, point_point);
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
    t_object *obj = object_create_for_sphere(s);
    t_tuple result = obj->shape->local_normal_at(obj->shape, point_point);
    cr_assert_float_eq(result.x, expected.x, 1e-6, "Normal X component is incorrect");
    cr_assert_float_eq(result.y, expected.y, 1e-6, "Normal Y component is incorrect");
    cr_assert_float_eq(result.z, expected.z, 1e-6, "Normal Z component is incorrect");
}

