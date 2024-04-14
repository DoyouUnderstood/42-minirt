#include "../include/mathematique.h"
#include "../include/shape.h"

// fonction for create material struct with default values
t_material material_create_default() 
{
    t_material m;
    t_pattern pattern = checker_pattern_create(color_create(1, 0.6, 0.5), color_create(1, 0.6, 1));

    // m.color = (t_color){0, 0, 1};
    m.ambient = 0.1;
    m.diffuse = 0.9;
    m.specular = 0.9;
    m.shininess = 200.0;
    m.pattern = pattern;

    return m;
}
