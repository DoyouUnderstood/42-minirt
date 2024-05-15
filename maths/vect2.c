/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:25:38 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/15 17:36:15 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mathematique.h"
#include "maths.h"

// fonction pour normaliser un vecteur
t_tuple	vector_normalize(t_tuple a)
{
	t_tuple	result;
	double	length;

	length = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	if (length != 0)
	{
		result.x = a.x / length;
		result.y = a.y / length;
		result.z = a.z / length;
		result.w = 0;
	}
	else
	{
		result.x = 0;
		result.y = 0;
		result.z = 0;
		result.w = 0;
	}
	return (result);
}

// Fonction pour inverser un vecteur.
t_tuple	vector_negate(t_tuple v)
{
	t_tuple	result;

	result.x = -v.x;
	result.y = -v.y;
	result.z = -v.z;
	result.w = v.w;
	return (result);
}

// mutlitiplication de vecteur.
t_tuple	vector_cross(t_tuple a, t_tuple b)
{
	return ((t_tuple){.x = a.y * b.z - a.z * b.y, .y = a.z * b.x - a.x * b.z,
		.z = a.x * b.y - a.y * b.x, .w = 0.0});
}
