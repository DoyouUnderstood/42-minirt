/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:13:30 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 12:37:54 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pattern.h"
#include "color.h"

#include <stdlib.h>

void	pattern_init_default(t_pattern *pattern)
{
	pattern->color_a = color_create(0, 0, 0);
	pattern->color_b = color_create(1, 1, 1);
	pattern->transformations.base = matrix_identity();
	pattern->transformations.inverse
		= matrix_inverse(pattern->transformations.base);
	pattern->pattern_at = NULL;
}