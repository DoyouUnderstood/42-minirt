/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:25:29 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/21 14:40:10 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

// Fonction pour initialiser un rayon
t_ray	ray_create(t_tuple origin, t_tuple direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

// Fonction pour calculer le point à la distance t le long du rayon
t_tuple	t_point_position(const t_ray *ray, double t)
{
	t_tuple	displacement;

	displacement = tuple_scale(ray->direction, t, t, t);
	return (tuple_add(ray->origin, displacement));
}

// fonction pour transformer un rayon suivant une matrix
t_ray	ray_transform(t_matrix mat, t_ray ray)
{
	t_ray	transformed_ray;

	transformed_ray.origin = matrix_mult_tuple(mat, ray.origin);
	transformed_ray.direction = matrix_mult_tuple(mat, ray.direction);
	return (transformed_ray);
}
