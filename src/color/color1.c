/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:42:33 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 09:53:25 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "utils.h"

// Fonction pour créer une couleur
t_color	color_create(double r, double g, double b)
{
	t_color	new_color;

	new_color.r = r;
	new_color.g = g;
	new_color.b = b;
	return (new_color);
}

// Fonction pour comparer deux couleurs avec une certaine tolérance
bool	color_eq(t_color c1, t_color c2)
{
	return (double_eq(c1.r, c2.r) && double_eq(c1.g, c2.g) && double_eq(c1.b, c2.b));
}

// fonction pour ajouter des couleurs.
t_color	color_add(t_color c1, t_color c2)
{
	t_color	result;

	result.r = c1.r + c2.r;
	result.g = c1.g + c2.g;
	result.b = c1.b + c2.b;
	return (result);
}

t_color	color_subtract(t_color c1, t_color c2)
{
	return ((t_color){c1.r - c2.r, c1.g - c2.g, c1.b - c2.b});
}
