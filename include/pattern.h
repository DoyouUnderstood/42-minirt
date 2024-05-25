/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:08:13 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 09:55:01 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATTERN_H
# define PATTERN_H

# include "color.h"
# include "matrix.h"
# include "tuple.h"

struct s_pattern;

typedef t_color	(*t_pattern_at)(const struct s_pattern *pattern, t_tuple point);

typedef struct s_pattern
{
	t_color			color_a;
	t_color			color_b;
	t_matrix		transform;
	t_pattern_at	pattern_at;
}	t_pattern;

t_pattern						*checker_pattern_create(t_color color1,
									t_color color2);
t_pattern						*ring_pattern_create(t_color color1,
									t_color color2);
t_pattern						*gradient_pattern_create(t_color color1,
									t_color color2);
t_pattern						*stripe_pattern_create(t_color color1,
									t_color color2);

#endif