/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:55:10 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/15 16:31:18 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../object/test_shape.h"
#include "graphics.h"
#include <math.h>
#include <stdio.h>

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
