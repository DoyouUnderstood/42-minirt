/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:01:36 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 06:46:44 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "color.h"
# include "tuple.h"

typedef struct s_light
{
	t_color	color;
	t_tuple	pos;
	double	intensity;
}			t_light;

typedef struct s_amb_light
{
	t_color	color;
	double	intensity;
}			t_amb_light;

t_light	*light_create(t_color color, t_tuple position,
			double intensity);

#endif
