/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:00:27 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/24 16:31:34 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "material.h"
#include "pattern.h"

#include <stdlib.h>

void	material_init_default(t_material *material)
{
	material->color = color_create(0, 0, 0);
	material->amb.color = color_create(0, 0, 1);
	material->amb.ambient = 0.3;
	material->diffuse = 0;
	material->specular = 0.9;
	material->shininess = 200.0;
	material->reflectiv = 0.0;
	material->pattern = NULL;
	material->refractive_index = 1.0;
	material->transparency = 0.0;
}

// fonction for create material struct with default values
t_material	*material_create_default(t_color *color, double reflectiv,
		t_pattern *pattern)
{
	t_material	*m;

	m = malloc(sizeof(t_material));
	m->color = *color;
	m->amb.color = (t_color){0, 0, 1};
	m->amb.ambient = 0.3;
	m->diffuse = 0;
	m->specular = 0.9;
	m->shininess = 200.0;
	m->reflectiv = reflectiv;
	m->pattern = pattern;
	m->refractive_index = 1.0;
	m->transparency = 0.0;
	return (m);
}
