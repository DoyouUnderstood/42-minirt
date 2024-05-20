/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:26:50 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/20 13:35:19 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include "object.h"

#include <stdlib.h>

t_intersection	*intersection_create(t_object *obj, double t)
{
	t_intersection	*intersection;

	intersection = malloc(sizeof(*intersection));
	if (!intersection)
		return (NULL);
	intersection->obj = obj;
	intersection->t = t;
	return (intersection);
}

t_intersection	*intersection_create_pair(t_object *obj, double t0, double t1)
{
	t_intersection	*intersections;

	intersections = malloc(sizeof(*intersections) * 2);
	if (!intersections)
		return (NULL);
	intersections[0].obj = obj;
	intersections[0].t = t0;
	intersections[1].obj = obj;
	intersections[1].t = t1;
	return (intersections);
}