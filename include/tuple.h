/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:01:31 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/22 19:09:16 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUPLE_H
# define TUPLE_H

# include <stdbool.h>

typedef struct s_tuple
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_tuple;

// ============ TUPLE =============

bool	tuple_eq(t_tuple a, t_tuple b);
t_tuple	tuple_add(t_tuple a, t_tuple b);
t_tuple	tuple_subtract(t_tuple a, t_tuple b);
t_tuple	tuple_scale(t_tuple point, double sx, double sy,
			double sz);
double	tuple_magnitude(const t_tuple *t);

// ============== POINT ===============

t_tuple	point_create(double x, double y, double z);

// ============== VECTEUR ===============

t_tuple	vector_create(double x, double y, double z);
t_tuple	vector_negate(t_tuple v);
t_tuple	vector_normalize(t_tuple a);
double	vector_dot(t_tuple a, t_tuple b);
t_tuple	vector_cross(t_tuple a, t_tuple b);
t_tuple	vector_reflect(t_tuple incident, t_tuple normal);

#endif
