/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:01:43 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 11:20:49 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// material.h
#ifndef MATERIAL_H
# define MATERIAL_H

# include "color.h"
# include "light.h"
# include "pattern.h"

typedef struct s_material
{
	t_color		color;
	t_amb_light	amb;
	double		diffuse;
	double		specular;
	double		shininess;
	t_pattern	pattern;
	double		reflectiv;
	double		transparency;
	double		refractive_index;
}				t_material;

void		material_init_default(t_material *material);

#endif