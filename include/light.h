#ifndef LIGHT_H
#define LIGHT_H

#include "types.h"

typedef struct s_light
{ 
	t_color intensity;
	t_tuple pos;
	double diffuse;
}	t_light;

typedef struct s_amb_light
{
	t_color color;
	double ambient;
}	t_amb_light;

#endif // LIGHT_H
