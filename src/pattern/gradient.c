/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:00:40 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/28 11:58:56 by alletond         ###   ########.fr       */
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

	transformed_point = matrix_mult_tuple(pattern->transformations.inverse,
			point);
	fraction = transformed_point.x - floor(transformed_point.x);
	distance = color_subtract(pattern->color_b, pattern->color_a);
	return (color_add(pattern->color_a, color_multiply_scalar(distance,
				fraction)));
}

void	pattern_init_gradient(t_pattern *pattern, t_color color1,
	t_color color2)
{
	pattern->color_a = color1;
	pattern->color_b = color2;
	pattern->transformations.base = matrix_identity();
	pattern->transformations.inverse
		= matrix_inverse(pattern->transformations.base);
	pattern->pattern_at = gradient_at;
}
