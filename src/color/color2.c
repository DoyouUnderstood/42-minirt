/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:42:33 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/23 14:01:11 by erabbath         ###   ########.fr       */
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

t_color	color_from_255(t_color_255 color_255)
{
	t_color	new_color;

	new_color.r = color_255.r / 255.0;
	new_color.g = color_255.g / 255.0;
	new_color.b = color_255.b / 255.0;
	return (new_color);
}

bool	color_255_validate(t_color_255 color_255)
{
	return (!(color_255.r < 0
		|| color_255.r > 255
		|| color_255.g < 0
		|| color_255.g > 255
		|| color_255.b < 0
		|| color_255.b > 255));
}
