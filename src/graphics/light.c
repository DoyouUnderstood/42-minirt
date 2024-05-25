/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:32:20 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 06:59:14 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"
#include "color.h"
#include "tuple.h"

#include <stdlib.h>

char	*amb_light_validate(t_amb_light *amb_light)
{
	if (amb_light->intensity < 0.0 || amb_light->intensity > 1.0)
		return ("Ambient light: Invalid intensity");
	return (NULL);
}

char	*light_validate(t_light *light)
{
	if (light->intensity < 0.0 || light->intensity > 1.0)
		return ("Light: Invalid intensity");
	return (NULL);
}
