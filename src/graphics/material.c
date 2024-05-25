/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:00:27 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 11:20:57 by erabbath         ###   ########.fr       */
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
	material->amb.intensity = 0.3;
	material->diffuse = 0;
	material->specular = 0.9;
	material->shininess = 200.0;
	material->reflectiv = 0.0;
	pattern_init_default(&material->pattern);
	material->refractive_index = 1.0;
	material->transparency = 0.0;
}
