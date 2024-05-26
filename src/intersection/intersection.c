/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:26:50 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 21:48:40 by erabbath         ###   ########.fr       */
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
t_intersection	*intersection_hit(t_intersection *intersections, int count)
{
	t_intersection	*hit;
	double			min_t;
	int				i;

	i = 0;
	hit = NULL;
	min_t = DBL_MAX;
	while (i < count)
	{
		if (intersections[i].t > 0 && intersections[i].t < min_t)
		{
			hit = &intersections[i];
			min_t = intersections[i].t;
		}
		i++;
	}
	return (hit);
}
