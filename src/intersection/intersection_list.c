/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:23:46 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/27 16:37:14 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include "libft.h"
#include "object.h"

#include <stdlib.h>

char	*intersection_arr_resize(t_intersection_arr *arr)
{
	t_intersection	*new_intersections;

	new_intersections = malloc(sizeof(t_intersection) * (arr->capacity * 2));
	if (!new_intersections)
		return ("Intersection array: malloc error");
	ft_memcpy(new_intersections, arr->intersections,
			sizeof(t_intersection) * arr->count);
	free(arr->intersections);
	arr->intersections = new_intersections;
	return (NULL);
}

char	*intersection_arr_init(t_intersection_arr *arr, int init_capacity)
{
	arr->capacity = init_capacity;
	arr->count = 0;
	arr->intersections = malloc(sizeof(t_intersection) * arr->capacity);
	if (!arr->intersections)
		return ("Intersection array: malloc error");
	return (NULL);
}

void	intersection_arr_clean(t_intersection_arr *arr)
{
	free(arr->intersections);
}

char	*intersection_arr_add(t_intersection_arr *arr, t_object *obj, double t)
{
	char	*error;

	error = NULL;
	if (arr->count == arr->capacity)
		error = intersection_arr_resize(arr);
	if (error)
		return (error);
	arr->intersections[arr->count].obj = obj;
	arr->intersections[arr->count++].t = t;
	return (NULL);
}

void	intersection_arr_sort(t_intersection_arr *arr)
{
	int				i;
	int				j;
	t_intersection	intersection_i;

	i = 1;
	while (i < arr->count)
	{
		intersection_i = arr->intersections[i];
		j = i - 1;
		while (j >= 0 && arr->intersections[j].t > intersection_i.t)
		{
			arr->intersections[j + 1] = arr->intersections[j];
			j--;
		}
		arr->intersections[j + 1] = intersection_i;
		i++;
	}
}
