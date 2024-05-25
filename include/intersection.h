/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:26:50 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 11:53:25 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H

# include "object.h"

typedef struct s_object t_object;

typedef struct s_intersection
{
	double					t;
	t_object				*obj;
}							t_intersection;

t_intersection	*intersection_create(t_object *obj, double t);
t_intersection	*intersection_create_pair(t_object *obj, double t0, double t1);
bool			intersection_realloc(t_intersection **intersections,
					int required_capacity, int *capacity);
t_intersection	*intersection_hit(t_intersection *intersections, int count);

#endif