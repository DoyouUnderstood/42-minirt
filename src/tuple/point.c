/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:25:26 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/28 11:58:07 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"

// fonction pour cree un point.
t_tuple	point_create(double x, double y, double z)
{
	return ((t_tuple){x, y, z, 1.0});
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
