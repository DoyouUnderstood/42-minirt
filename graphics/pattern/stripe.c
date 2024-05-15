/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stripe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:00:47 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/15 16:00:48 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shape.h"
#include "../../object/test_shape.h"
#include "../graphics.h"

t_pattern	*stripe_pattern_create(t_color color1, t_color color2)
{
	t_pattern	*pattern;

	pattern = malloc(sizeof(t_pattern));
	pattern->color_a = color1;
	pattern->color_b = color2;
	pattern->transform = matrix_init_identity();
	pattern->pattern_at = stripe_at;
	return (pattern);
}

t_pattern	stripe_pattern(t_color a, t_color b)
{
	t_pattern	pattern;

	pattern.color_a = a;
	pattern.color_b = b;
	return (pattern);
}

t_color	stripe_at(const t_pattern *pattern, t_tuple point)
{
	t_tuple	transformed_point;

	transformed_point = matrix_mult(matrix_inverse(pattern->transform),
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

t_color	stripe_at_object(const t_pattern *pattern, const t_object *object,
		t_tuple point)
{
	t_tuple	object_point;

	object_point = matrix_mult(matrix_inverse(object->shape->transformation),
			point);
	return (pattern->pattern_at(pattern, object_point));
}
