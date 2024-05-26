/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:26:50 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/26 15:29:09 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H

# include "object.h"

typedef struct s_object t_object;

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

typedef struct s_intersection_pair
{
	int			count;
	double		t[2];
	t_object	*obj;
}	t_intersection_pair;

bool			intersection_realloc(t_intersection **intersections,
					int required_capacity, int *capacity);
t_intersection	*intersection_hit(t_intersection *intersections, int count);

char	*intersection_arr_init(t_intersection_arr *arr, int init_capacity);
void	intersection_arr_clean(t_intersection_arr *arr);
char	*intersection_arr_add(t_intersection_arr *arr, t_object *obj, double t);
void	intersection_arr_sort(t_intersection_arr *arr);

#endif