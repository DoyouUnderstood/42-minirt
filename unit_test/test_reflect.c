#include <criterion/criterion.h>
#include <math.h>
#include "../include/mathematique.h"
#include "../include/shape.h"
#include "../object/test_shape.h"

Test(reflection_tests, vector_approaching_at_45_degrees) 
{
    t_tuple v = {1, -1, 0, 0};
    t_tuple n = {0, 1, 0, 0};
    t_tuple expected = {1, 1, 0, 0};
    
    t_tuple r = reflect(v, n);
    
    cr_assert(tuple_eq(r, expected), "Reflection of v=(1,-1,0) off n=(0,1,0) should be (1,1,0)");
}

Test(reflection_tests, vector_off_slanted_surface) 
{
    t_tuple v = {0, -1, 0, 0};
    t_tuple n = {sqrt(2)/2, sqrt(2)/2, 0, 0};
    t_tuple expected = {1, 0, 0, 0};
    
    t_tuple r = reflect(v, n);
    
    cr_assert(tuple_eq(r, expected), "Reflection of v=(0,-1,0) off n=(√2/2, √2/2, 0) should be (1,0,0)");
}