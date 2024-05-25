/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:08:13 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 12:35:19 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATTERN_H
# define PATTERN_H

# include "color.h"
# include "matrix.h"
# include "tuple.h"

struct s_pattern;

typedef t_color	(*t_pattern_at)(const struct s_pattern *pattern, t_tuple point);

typedef struct s_pattern_transf
{
	t_matrix	base;
	t_matrix	inverse;
}	t_pattern_transf;

typedef struct s_pattern
{
	t_color				color_a;
	t_color				color_b;
	t_pattern_transf	transformations;
	t_pattern_at		pattern_at;
}	t_pattern;

void	pattern_init_default(t_pattern *pattern);
void	pattern_init_checker(t_pattern *pattern, t_color color1,
			t_color color2);
void	pattern_init_ring(t_pattern *pattern, t_color color1, t_color color2);
void	pattern_init_gradient(t_pattern *pattern, t_color color1,
			t_color color2);
void	pattern_init_stripe(t_pattern *pattern, t_color color1,
			t_color color2);

#endif