/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:26:50 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/26 19:03:12 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include "object.h"

#include <float.h>
#include <stdlib.h>

// Fonction pour identifier le hit parmi une collection d'intersections
t_intersection	*intersection_hit(t_intersection_arr *intersections)
{
	int				i;

	i = 0;
	while (i < intersections->count)
	{
		if (intersections->intersections[i].t > 0.0)
			return (&intersections->intersections[i]);
		i++;
	}
	return (NULL);
}
