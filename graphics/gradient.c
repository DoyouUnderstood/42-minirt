#include "../include/shape.h"
#include "../include/graphics.h"
#include "../object/test_shape.h"

t_color color_subtract(t_color c1, t_color c2) {
    return (t_color){c1.r - c2.r, c1.g - c2.g, c1.b - c2.b};
}

t_color gradient_at(const t_pattern *pattern, t_tuple point);

t_pattern gradient_pattern_create(t_color color1, t_color color2) {
    t_pattern pattern;
    pattern.color_a = color1;
    pattern.color_b = color2;
    pattern.transform = matrix_init_identity();
    pattern.pattern_at = gradient_at;
    return pattern;
}

t_color gradient_at(const t_pattern *pattern, t_tuple point) 
{
    t_tuple transformed_point = matrix_multiply_by_tuple(matrix_inverse(pattern->transform), point);
    double fraction = transformed_point.x - floor(transformed_point.x);
    t_color distance = color_subtract(pattern->color_b, pattern->color_a);
    return color_add(pattern->color_a, color_multiply_scalar(distance, fraction));
}

