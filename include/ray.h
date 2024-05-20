/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:08:19 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/20 11:04:19 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "tuple.h"
# include "matrix.h"

typedef struct s_ray
{
	t_tuple						origin;
	t_tuple						direction;
}	t_ray;

t_ray	ray_create(t_tuple origin, t_tuple direction);
t_tuple	t_point_position(const t_ray *ray, double t);
t_ray	ray_transform(t_matrix mat, t_ray ray);

#endif