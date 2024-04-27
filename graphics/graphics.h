#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "../include/mathematique.h"
#include "../include/types.h"
#include "../include/light.h"
#include "../include/pattern.h"

#include <stdint.h>
typedef struct s_object t_object;
typedef struct s_intersection t_intersection;
typedef struct s_ray t_ray;
typedef struct s_world t_world;


// ===== PATTERN ===== 

t_pattern *checker_pattern_create(t_color color1, t_color color2);

t_pattern *ring_pattern_create(t_color color1, t_color color2);
t_color ring_at(const t_pattern *pattern, t_tuple point);

t_pattern *gradient_pattern_create(t_color color1, t_color color2);
t_color gradient_at(const t_pattern *pattern, t_tuple point);

void set_pattern_transform(t_pattern *pattern, t_matrix transform);
t_pattern *stripe_pattern_create(t_color color1, t_color color2);
t_pattern stripe_pattern(t_color a, t_color b); 
t_color stripe_at(const t_pattern *pattern, t_tuple point);
t_color stripe_at_object(const t_pattern *pattern, const t_object *object, t_tuple point);


t_color convert_color_255_to_1(int r, int g, int b);
t_color color_create(double r, double g, double b);
bool color_eq(t_color c1, t_color c2);
t_color color_at(t_world *world,t_ray *ray, int remaining);
t_color color_add(t_color c1, t_color c2);
t_color color_multiply(t_color c1, t_color c2);
t_color color_multiply_alternativ(t_color c1, t_color c2);
t_color color_multiply_scalar(t_color c, double scalar);
uint32_t color_to_rgb(float red, float green, float blue);
t_light *light_create(t_color color, t_tuple position, double diffuse);
t_color calculate_color(t_intersection *closest_hit, t_ray *ray, t_light *light);
t_material *material_create_default(t_color *color);

t_color lighting(const t_material *material, const t_object *object, const t_light *light, const t_tuple *position, const t_tuple *eyev, const t_tuple *normalv, bool in_shadow);

#endif