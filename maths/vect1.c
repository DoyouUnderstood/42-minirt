/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:25:38 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/15 17:36:00 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mathematique.h"
#include "maths.h"

// Fonction pour créer un vecteur
t_tuple	vector_create(double x, double y, double z)
{
	return ((t_tuple){x, y, z, 0.0});
}

// fonction pour ajouter 2 vecteurs
t_tuple	vector_add(t_tuple v1, t_tuple v2)
{
	t_tuple	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	result.w = 0.0;
	return (result);
}

// fonction de mise a l'echelle d'un vecteur.
t_tuple	vector_scale(t_tuple v, double scalar)
{
	t_tuple	result;

	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	result.w = v.w;
	return (result);
}

// fonction de produit scalaire de vecteur.
double	vector_dot(t_tuple a, t_tuple b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

// fonction pour multiplier toute les composantes d'un vec pour un scalaire
t_tuple	vector_multiply(t_tuple a, double scalar)
{
	t_tuple	result;

	result.x = a.x * scalar;
	result.y = a.y * scalar;
	result.z = a.z * scalar;
	result.w = a.w;
	return (result);
}
