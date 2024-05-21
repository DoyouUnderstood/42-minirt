/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:26:50 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/16 16:55:39 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "tuple.h"
# include "intersection.h"
# include "object.h"

typedef struct s_sphere_data
{
	t_tuple	center;
	double	diameter;
}	t_sphere_data;

typedef struct s_sphere_intersect_data
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	discriminant_sqrt;
	t_tuple	sphere_to_ray;
}	t_sphere_intersect_data;

t_object	*sphere_create(t_tuple center,
				double diameter, t_material_specs specs);

#endif