/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:32:20 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/16 16:33:03 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"
#include "color.h"
#include "tuple.h"

#include <stdlib.h>

t_light	*light_create(t_color color, t_tuple position, double diffuse)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	light->diffuse = diffuse;
	light->intensity = color;
	light->pos = position;
	return (light);
}
