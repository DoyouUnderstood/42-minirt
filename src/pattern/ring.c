/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ring.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:00:43 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 12:38:42 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pattern.h"
#include "color.h"

#include <math.h>
#include <stdlib.h>

static t_color	ring_at(const t_pattern *pattern, t_tuple point)
{
	t_tuple	transformed_point;
	double	distance;

	transformed_point = matrix_mult_tuple(pattern->transformations.inverse,
			point);
	distance = sqrt(transformed_point.x * transformed_point.x
			+ transformed_point.z * transformed_point.z);
	if ((int)floor(distance) % 2 == 0)
		return (pattern->color_a);
	else
		return (pattern->color_b);
}

void	pattern_init_ring(t_pattern *pattern, t_color color1, t_color color2)
{
	pattern->color_a = color1;
	pattern->color_b = color2;
	pattern->transformations.base = matrix_identity();
	pattern->transformations.inverse
		= matrix_inverse(pattern->transformations.base);
	pattern->pattern_at = ring_at;
}
