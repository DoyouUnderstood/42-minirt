#include <math.h>

#include "../include/shape.h"
#include "../include/graphics.h"
#include "../object/test_shape.h"

t_color checker_at(const t_pattern *pattern, t_tuple point) {
    int check = (int)(floor(point.x) + floor(point.y) + floor(point.z));
    if (check % 2 == 0) {
        return pattern->color_a;
    } else {
        return pattern->color_b;
    }
}

t_pattern *checker_pattern_create(t_color color1, t_color color2) {
    t_pattern *pattern;
    pattern = malloc(sizeof(t_pattern));
    pattern->color_a = color1;
    pattern->color_b = color2;
    pattern->pattern_at = checker_at;
    return (pattern);
}

