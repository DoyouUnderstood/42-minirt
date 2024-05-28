/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:26:50 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/28 12:03:28 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H

# include "object.h"

typedef struct s_object	t_object;

typedef struct s_intersection
{
	double		t;
	t_object	*obj;
}	t_intersection;

typedef struct s_intersection_arr
{
	int				capacity;
	int				count;
	t_intersection	*intersections;
}	t_intersection_arr;

t_intersection	*intersection_hit(t_intersection_arr *intersections);

char			*intersection_arr_init(t_intersection_arr *arr,
					int init_capacity);
void			intersection_arr_clean(t_intersection_arr *arr);
char			*intersection_arr_add(t_intersection_arr *arr, t_object *obj,
					double t);
void			intersection_arr_sort(t_intersection_arr *arr);

#endif