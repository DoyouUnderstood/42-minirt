/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:42:33 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/16 16:55:29 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "utils.h"

// Fonction pour multiplier une couleur par un scalaire.
int	color_to_int(t_color color)
{
	int	r;
	int	g;
	int	b;

	r = dclamp(color.r, 0.0, 1.0) * 255;
	g = dclamp(color.g, 0.0, 1.0) * 255;
	b = dclamp(color.b, 0.0, 1.0) * 255;
	return ((r << 16) | (g << 8) | b);
}

t_color	color_from_rgb(int r, int g, int b)
{
	t_color	new_color;

	new_color.r = r / 255.0;
	new_color.g = g / 255.0;
	new_color.b = b / 255.0;
	return (new_color);
}
