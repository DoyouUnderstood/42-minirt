/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:25:26 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/16 15:46:53 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"

// fonction pour cree un point.
t_tuple	point_create(double x, double y, double z)
{
	return ((t_tuple){x, y, z, 1.0});
}
