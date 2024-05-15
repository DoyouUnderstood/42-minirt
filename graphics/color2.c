/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:42:33 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/15 16:34:22 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include <stdint.h>
#define COLOR_EPSILON 0.0001

// Fonction pour multiplier une couleur par un scalaire.
uint32_t	color_to_rgb(float red, float green, float blue)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	red = fmax(0, fmin(red, 1));
	green = fmax(0, fmin(green, 1));
	blue = fmax(0, fmin(blue, 1));
	r = (uint8_t)(red * 255);
	g = (uint8_t)(green * 255);
	b = (uint8_t)(blue * 255);
	return (((uint32_t)r << 16) | ((uint32_t)g << 8) | b);
}

// Fonction pour comparer deux couleurs avec une certaine tolérance
bool	color_eq(t_color c1, t_color c2)
{
	return (fabs(c1.r - c2.r) < COLOR_EPSILON && fabs(c1.g
			- c2.g) < COLOR_EPSILON && fabs(c1.b - c2.b) < COLOR_EPSILON);
}

// Fonction pour créer une couleur
t_color	color_create(double r, double g, double b)
{
	t_color	new_color;

	new_color.r = r;
	new_color.g = g;
	new_color.b = b;
	return (new_color);
}

t_color	convert_color_255_to_1(int r, int g, int b)
{
	t_color	new_color;

	new_color.r = r / 255.0;
	new_color.g = g / 255.0;
	new_color.b = b / 255.0;
	return (new_color);
}
