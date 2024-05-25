/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stripe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:00:47 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 11:31:13 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "object.h"
#include "pattern.h"

#include <math.h>
#include <stdlib.h>

static t_color	stripe_at(const t_pattern *pattern, t_tuple point)
{
	t_tuple	transformed_point;

	transformed_point = matrix_mult_tuple(matrix_inverse(pattern->transform),
			point);
	if ((int)floor(transformed_point.x) % 2 == 0)
	{
		return (pattern->color_a);
	}
	else
	{
		return (pattern->color_b);
	}
}

void	pattern_init_stripe(t_pattern *pattern, t_color color1,
	t_color color2)
{
	pattern->color_a = color1;
	pattern->color_b = color2;
	pattern->transform = matrix_identity();
	pattern->pattern_at = stripe_at;
}
