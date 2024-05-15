// material.h
#ifndef MATERIAL_H
# define MATERIAL_H

# include "light.h"
# include "pattern.h"
# include "types.h"

typedef struct s_material
{
	t_color		color;
	t_amb_light	amb;
	double		diffuse;
	double		specular;
	double		shininess;
	t_pattern	*pattern;
	double		reflectiv;
	double		transparency;
	double		refractive_index;
}				t_material;

#endif