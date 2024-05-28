/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:59:07 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/28 10:48:31 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_INTERNAL_H
# define OBJECT_INTERNAL_H

# include "object.h"

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
	double	half_h;
	bool	t0_intersects;
	bool	t1_intersects;
}	t_cylinder_intersect_calc;

typedef struct s_sphere_intersect_calc
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	discriminant_sqrt;
	double	t0;
	double	t1;
	t_tuple	sphere_to_ray;
}	t_sphere_intersect_calc;

#endif