/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:55:10 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/15 16:29:03 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../object/test_shape.h"
#include "graphics.h"
#include <math.h>
#include <stdio.h>

t_color	calculate_ef_c(const t_lighting *params)
{
	t_color		ef_c;
	t_matrix	t_inv;
	t_tuple		point_in_object_space;

	if (params && params->material && params->object && params->object->shape)
	{
		if (params->material->pattern && params->material->pattern->pattern_at)
		{
			t_inv = matrix_inverse(params->object->shape->transformation);
			point_in_object_space = matrix_mult(t_inv, *params->position);
			ef_c = params->material->pattern->pattern_at(
					params->material->pattern, point_in_object_space);
		}
		else
		{
			ef_c = color_multiply(params->material->color,
					params->light->intensity);
		}
	}
	else
	{
		ef_c = color_multiply(params->material->color,
				params->light->intensity);
	}
	return (ef_c);
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
