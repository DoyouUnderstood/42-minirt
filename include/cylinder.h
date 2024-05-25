/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:26:50 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 04:30:14 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "tuple.h"
# include "object.h"
# include "material.h"

typedef struct s_object t_object;

typedef struct s_cylinder_data
{
	t_tuple	center;
	t_tuple	axis;
	double	radius;
	double	height;
}	t_cylinder_data;

typedef struct s_cylinder_intersect_calc
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	discriminant_sqrt;
	double	y0;
	double	y1;
	double	t0;
	double	t1;
	double	half_height;
}	t_cylinder_intersect_calc;

t_object	*cylinder_create(t_cylinder_data *data, t_material *material);

#endif