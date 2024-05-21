/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:26:50 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/21 18:34:39 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTING_H
# define LIGHTING_H

# include "color.h"
# include "material.h"
# include "object.h"
# include "tuple.h"

typedef struct s_lighting
{
	t_material					*material;
	t_object					*object;
	t_light						*light;
	t_tuple						*position;
	t_tuple						*eyev;
	t_tuple						*normalv;
	bool						in_shadow;
}								t_lighting;

typedef struct s_specular_params
{
	t_tuple						lightv;
	t_tuple						normalv;
	t_tuple						eyev;
	const t_material			*material;
	const t_light				*light;
}								t_specular_params;

t_color							lighting(t_lighting *params);

#endif