/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:00:34 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 11:28:26 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "tuple.h"
#include "pattern.h"

#include <math.h>
#include <stdlib.h>

static t_color	checker_at(const t_pattern *pattern, t_tuple point)
{
	int	check;

	check = (int)(floor(point.x) + floor(point.y) + floor(point.z));
	if (check % 2 == 0)
		return (pattern->color_a);
	else
		return (pattern->color_b);
}

void	pattern_init_checker(t_pattern *pattern, t_color color1,
	t_color color2)
{
	pattern->color_a = color1;
	pattern->color_b = color2;
	pattern->transform = matrix_identity();
	pattern->pattern_at = checker_at;
}
