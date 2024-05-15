/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:42:33 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/15 14:44:33 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include <stdint.h>

// fonction pour ajouter des couleurs.
t_color	color_add(t_color c1, t_color c2)
{
	t_color	result;

	result.r = c1.r + c2.r;
	result.g = c1.g + c2.g;
	result.b = c1.b + c2.b;
	return (result);
}

// Fonction pour la multiplication de deux couleurs normalisées
t_color	color_multiply(t_color c1, t_color c2)
{
	t_color	result;

	result.r = c1.r * c2.r;
	result.g = c1.g * c2.g;
	result.b = c1.b * c2.b;
	return (result);
}

/// fonction alternative pour la multiplication de couleurs.
t_color	color_multiply_alternativ(t_color c1, t_color c2)
{
	t_color	result;

	result.r = (c1.r / 255.0) * (c2.r / 255.0) * 255;
	result.g = (c1.g / 255.0) * (c2.g / 255.0) * 255;
	result.b = (c1.b / 255.0) * (c2.b / 255.0) * 255;
	return (result);
}

t_light	*light_create(t_color color, t_tuple position, double diffuse)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	light->diffuse = diffuse;
	light->intensity = color;
	light->pos = position;
	return (light);
}

// Fonction pour multiplier une couleur par un scalaire.
t_color	color_multiply_scalar(t_color c, double scalar)
{
	t_color	result;

	result.r = c.r * scalar;
	result.g = c.g * scalar;
	result.b = c.b * scalar;
	return (result);
}
