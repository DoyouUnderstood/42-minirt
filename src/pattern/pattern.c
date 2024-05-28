/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:13:30 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/28 11:58:32 by alletond         ###   ########.fr       */
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
