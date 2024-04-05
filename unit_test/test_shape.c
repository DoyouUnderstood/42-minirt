#include <criterion/criterion.h>
#include "../include/graphics.h"
#include "../include/shape.h"

/*​ 	​Scenario​: The default transformation
​ 	  ​Given​ s ← test_shape()
​ 	  ​Then​ s.transform = identity_matrix
​ 	
​ 	​Scenario​: Assigning a transformation
​ 	  ​Given​ s ← test_shape()
​ 	  ​When​ set_transform(s, translation(2, 3, 4))
​ 	  ​Then​ s.transform = translation(2, 3, 4)     */

Test(test_shape, the_default_transformation)
{
    
}