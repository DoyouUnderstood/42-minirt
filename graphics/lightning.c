#include "../object/test_shape.h"
#include "graphics.h"
#include <math.h>
#include <stdio.h>

t_color					lighting(t_lighting *params);

t_color calculate_ef_c(const t_lighting *params) 
{
    t_color ef_c;

    // Check if params and its nested structures are not null
    if (params && params->material && params->object && params->object->shape) {
        if (params->material->pattern && params->material->pattern->pattern_at) {
            t_matrix t_inv = matrix_inverse(params->object->shape->transformation);
            t_tuple point_in_object_space = matrix_mult(t_inv, *params->position);
            ef_c = params->material->pattern->pattern_at(params->material->pattern, point_in_object_space);
        } else {
            ef_c = color_multiply(params->material->color, params->light->intensity);
        }
    } else {
       ef_c = color_multiply(params->material->color,
				params->light->intensity);
	}

    return ef_c;
}


t_color	calculate_ambient(t_color ef_c, double ambient_intensity)
{
	return (color_multiply_scalar(ef_c, ambient_intensity));
}

t_color	calculate_diffuse(t_color ef_c, double light_dot_normal,
		double intensity)
{
	return (color_multiply_scalar(ef_c, intensity * light_dot_normal));
}

typedef struct s_specular_params
{
	t_tuple				lightv;
	t_tuple				normalv;
	t_tuple				eyev;
	const t_material	*material;
	const t_light		*light;
}						t_specular_params;

t_color	calculate_specular(t_specular_params *params)
{
	t_tuple	reflectv;
	double	reflect_dot_eye;
	double	factor;
	t_color	result;

	reflectv = reflect(vector_negate(params->lightv), params->normalv);
	reflect_dot_eye = vector_dot(reflectv, params->eyev);
	if (reflect_dot_eye > 0)
	{
		factor = pow(reflect_dot_eye, params->material->shininess);
		result = color_multiply_scalar(params->light->intensity,
				params->material->specular * factor);
	}
	else
	{
		result = (t_color){0, 0, 0};
	}
	return (result);
}

t_specular_params	prepare_specular_params(t_lighting *params, t_tuple lightv)
{
	t_specular_params	spec_params;

	spec_params.normalv = *params->normalv;
	spec_params.eyev = *params->eyev;
	spec_params.material = params->material;
	spec_params.light = params->light;
	spec_params.lightv = lightv;
	return (spec_params);
}

t_color	calculate_lighting_components(t_lighting *params,
		double light_dot_normal, t_color ef_c)
{
	t_specular_params	spec_params;
	t_color				ambient;
	t_color				diffuse;
	t_color				specular;

	ambient = calculate_ambient(ef_c, params->material->amb.ambient);
	if (params->in_shadow)
	{
		return (ambient);
	}
	if (light_dot_normal > 0)
	{
		diffuse = calculate_diffuse(ef_c, light_dot_normal,
				params->light->diffuse);
		spec_params = prepare_specular_params(params,
				vector_normalize(tuple_subtract(params->light->pos,
						*params->position)));
		specular = calculate_specular(&spec_params);
	}
	else
	{
		diffuse = (t_color){0, 0, 0};
		specular = (t_color){0, 0, 0};
	}
	return (color_add(color_add(ambient, diffuse), specular));
}

t_color	lighting(t_lighting *params)
{
	t_color	ef_c;
	double	light_dot_normal;
	t_tuple	lightv;

	ef_c = calculate_ef_c(params);
	lightv = vector_normalize(tuple_subtract(params->light->pos,
				*params->position));
	light_dot_normal = vector_dot(lightv, *params->normalv);
	return (calculate_lighting_components(params, light_dot_normal, ef_c));
}
