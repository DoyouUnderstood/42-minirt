/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:32:20 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/22 19:17:36 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"
#include "color.h"
#include "tuple.h"

#include <stdlib.h>

t_light	*light_create(t_color color, t_tuple position, double intensity)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	light->intensity = intensity;
	light->color = color;
	light->pos = position;
	return (light);
}
