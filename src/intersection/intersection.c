/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:26:50 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/26 18:20:11 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include "object.h"

#include <float.h>
#include <stdlib.h>

bool	intersection_realloc(t_intersection **intersections,
		int required_capacity, int *capacity)
{
	t_intersection	*temp;

	while (required_capacity > *capacity)
		*capacity *= 2;
	// Retirer realloc
	temp = realloc(*intersections, (*capacity) * sizeof(t_intersection));
	if (!temp)
		return (false);
	*intersections = temp;
	return (true);
}

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
