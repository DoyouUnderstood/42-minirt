/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:00:40 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 09:53:49 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "tuple.h"
#include "pattern.h"

#include <math.h>
#include <stdlib.h>

static t_color	gradient_at(const t_pattern *pattern, t_tuple point)
{
	t_tuple	transformed_point;
	double	fraction;
	t_color	distance;

	transformed_point = matrix_mult_tuple(matrix_inverse(pattern->transform), point);
	fraction = transformed_point.x - floor(transformed_point.x);
	distance = color_subtract(pattern->color_b, pattern->color_a);
	return (color_add(pattern->color_a, color_multiply_scalar(distance,
				fraction)));
}

t_pattern	*gradient_pattern_create(t_color color1, t_color color2)
{
	t_pattern	*pattern;

	pattern = malloc(sizeof(t_pattern));
	pattern->color_a = color1;
	pattern->color_b = color2;
	pattern->transform = matrix_identity();
	pattern->pattern_at = gradient_at;
	return (pattern);
}
