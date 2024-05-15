/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:25:26 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/15 17:35:05 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mathematique.h"
#include "maths.h"

// fonction pour soustraire un vecteur d'un point.
t_tuple	point_sub_vector(t_tuple point, t_tuple vect)
{
	return ((t_tuple){point.x - vect.x, point.y - vect.y, point.z - vect.z,
		1.0});
}
