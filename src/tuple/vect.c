/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:25:38 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/22 19:07:15 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"
#include <math.h>

// Fonction pour créer un vecteur
t_tuple	vector_create(double x, double y, double z)
{
	return ((t_tuple){x, y, z, 0.0});
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

// fonction de produit scalaire de vecteur.
double	vector_dot(t_tuple a, t_tuple b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

// mutlitiplication de vecteur.
t_tuple	vector_cross(t_tuple a, t_tuple b)
{
	return ((t_tuple){.x = a.y * b.z - a.z * b.y, .y = a.z * b.x - a.x * b.z,
		.z = a.x * b.y - a.y * b.x, .w = 0.0});
}

t_tuple	vector_reflect(t_tuple incident, t_tuple normal)
{
	double	scale;
	t_tuple	scaled_normal;
	t_tuple	reflection;

	scale = 2 * vector_dot(incident, normal);
	scaled_normal = tuple_scale(normal, scale, scale, scale);
	reflection = tuple_subtract(incident, scaled_normal);
	return (reflection);
}
