/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computation1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:24:11 by ltd               #+#    #+#             */
/*   Updated: 2024/05/21 11:14:43 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "mathematique.h"
#include "shape_old.h"
#include "libft.h"
#include "../object/test_shape.h"

bool	realoc_inter(t_intersection **intersections,
		int required_capacity, int *capacity)
{
	t_intersection	*temp;

	while (required_capacity > *capacity)
	{
		*capacity *= 2;
	}
	temp = realloc(*intersections, (*capacity) * sizeof(t_intersection));
	if (!temp)
	{
		return (false);
	}
	*intersections = temp;
	return (true);
}
