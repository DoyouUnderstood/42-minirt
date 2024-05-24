/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:26:50 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/24 17:13:02 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

#include "color.h"
#include "tuple.h"
#include "object.h"
#include "pattern.h"
#include "material.h"

typedef struct s_plane_data
{
	t_tuple	center;
	t_tuple	direction;
}	t_plane_data;

t_object	*plane_create(t_plane_data *data, t_material *material);

#endif