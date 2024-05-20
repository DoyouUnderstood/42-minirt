/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ring.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:00:43 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/16 16:22:18 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shape.h"
#include "../../object/test_shape.h"
#include "../graphics.h"

t_pattern	*ring_pattern_create(t_color color1, t_color color2)
{
	t_pattern	*pattern;

	pattern = malloc(sizeof(t_pattern));
	pattern->color_a = color1;
	pattern->color_b = color2;
	pattern->pattern_at = ring_at;
	pattern->transform = matrix_identity();
	return (pattern);
}

t_color	ring_at(const t_pattern *pattern, t_tuple point)
{
	t_tuple	transformed_point;
	double	distance;

	transformed_point = matrix_mult_tuple(matrix_inverse(pattern->transform),
			point);
	distance = sqrt(transformed_point.x * transformed_point.x
			+ transformed_point.z * transformed_point.z);
	if ((int)floor(distance) % 2 == 0)
	{
		return (pattern->color_a);
	}
	else
	{
		return (pattern->color_b);
	}
}
