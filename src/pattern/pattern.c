/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:13:30 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 11:28:13 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pattern.h"
#include "color.h"

#include <stdlib.h>

void	pattern_init_default(t_pattern *pattern)
{
	pattern->color_a = color_create(0, 0, 0);
	pattern->color_b = color_create(1, 1, 1);
	pattern->transform = matrix_identity();
	pattern->pattern_at = NULL;
}