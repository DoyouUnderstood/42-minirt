/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:26:50 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/21 10:43:23 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

#include "color.h"
#include "tuple.h"
#include "object.h"
#include "pattern.h"

typedef struct s_plane_data
{
	t_tuple	center;
}	t_plane_data;

t_object	*plane_create(t_color color, t_tuple center,
				t_pattern *pattern, t_tuple direction);

#endif