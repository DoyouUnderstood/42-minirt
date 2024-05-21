/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:00:27 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/21 14:15:31 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape_old.h"
#include "graphics.h"

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

t_material	*material_create_default_plane(t_color *color, t_pattern *pattern)
{
	t_material	*m;

	m = malloc(sizeof(t_material));
	m->color = *color;
	m->amb.color = (t_color){1, 1, 1};
	m->amb.ambient = 0.3;
	m->specular = 0.9;
	m->shininess = 200.0;
	m->reflectiv = 0.5;
	m->refractive_index = 0.0;
	m->transparency = 0.0;
	m->pattern = pattern;
	return (m);
}
