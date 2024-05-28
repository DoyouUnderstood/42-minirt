/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:01:31 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/28 11:57:57 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"
#include "utils.h"

#include <math.h>

// Fonction pour comparer deux tuples avec la précision standard
bool	tuple_eq(t_tuple a, t_tuple b)
{
	return (double_eq(a.x, b.x) && double_eq(a.y, b.y)
		&& double_eq(a.z, b.z) && double_eq(a.w, b.w));
}

t_tuple	tuple_add(t_tuple a, t_tuple b)
{
	t_tuple	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	result.w = a.w + b.w;
	return (result);
}

t_tuple	tuple_subtract(t_tuple a, t_tuple b)
{
	t_tuple	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	result.w = a.w - b.w;
	return (result);
}

// Fonction Applique une mise à l'échelle sur un point ou un vecteur.
t_tuple	tuple_scale(t_tuple point, double sx, double sy, double sz)
{
	point.x *= sx;
	point.y *= sy;
	point.z *= sz;
	return (point);
}

// Fonction pour calculer la magnitude d'un tuple/vecteur
double	tuple_magnitude(const t_tuple *t)
{
	return (sqrt(t->x * t->x + t->y * t->y + t->z * t->z));
}
