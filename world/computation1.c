/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computation1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltd <ltd@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:24:11 by ltd               #+#    #+#             */
/*   Updated: 2024/05/15 17:29:16 by ltd              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../include/mathematique.h"
#include "../include/shape.h"
#include "../lib/libft/libft.h"
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
