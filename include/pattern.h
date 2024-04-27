#ifndef PATTERN_H
#define PATTERN_H

#include "types.h"

typedef struct s_pattern {
    t_color color_a;
    t_color color_b;
    t_matrix transform;
    t_color (*pattern_at)(const struct s_pattern *pattern, t_tuple point);
} t_pattern;

#endif