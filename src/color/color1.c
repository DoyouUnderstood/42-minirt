/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:42:33 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/16 16:45:53 by erabbath         ###   ########.fr       */
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

// Fonction pour la multiplication de deux couleurs normalisées
t_color	color_multiply(t_color c1, t_color c2)
{
	t_color	result;

	result.r = c1.r * c2.r;
	result.g = c1.g * c2.g;
	result.b = c1.b * c2.b;
	return (result);
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
