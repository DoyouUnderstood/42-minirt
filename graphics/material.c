#include "../include/mathematique.h"
#include "../include/shape.h"

// fonction for create material struct with default values
t_material material_create_default() 
{
    t_material m;
    
    m.color = (t_color){1, 1, 1};
    m.ambient = 0.1;
    m.diffuse = 0.9;
    m.specular = 0.9;
    m.shininess = 200.0;

    return m;
}
