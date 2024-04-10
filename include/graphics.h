#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "mathematique.h"
#include <stdint.h>

typedef struct s_intersection t_intersection;
typedef enum e_obj_type t_obj_type;
typedef struct s_ray t_ray;
typedef struct s_world t_world;

typedef struct s_color
{
	double r;
	double g;
	double b;
}					t_color;

typedef struct s_light
{ 
	t_color intensity;
	t_tuple pos;
}	t_light;


typedef struct s_material
{
	t_color color;
	double ambient;
	double diffuse;
	double specular;
	double shininess;
}	t_material;


t_color color_at(t_world *world, t_ray *ray);
t_color color_add(t_color c1, t_color c2);
t_color color_multiply(t_color c1, t_color c2);
t_color color_multiply_alternativ(t_color c1, t_color c2);
t_color color_multiply_scalar(t_color c, double scalar);
uint32_t color_to_rgb(float red, float green, float blue);
t_light *light_create(t_color color, t_tuple position);
t_color calculate_color(t_intersection *closest_hit, t_ray *ray, t_light *light);
t_material material_create_default();

t_color lighting(const t_material *material, const t_light *light, const t_tuple *position, const t_tuple *eyev, const t_tuple *normalv, bool in_shadow);

#endif