/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:17:31 by ltd               #+#    #+#             */
/*   Updated: 2024/05/25 21:38:28 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computation.h"
#include "intersection.h"
#include "world.h"
#include "tuple.h"

#include "libft.h"
#define EPSILON 0.00001

void	prepare_computations(t_computations *comps,
		const t_intersection *intersection, const t_ray *ray)
{
	if (comps == NULL)
		return ;
	comps->t = intersection->t;
	comps->object = intersection->obj;
	comps->point = t_point_position(ray, intersection->t);
	comps->eyev = vector_negate(ray->direction);
	comps->normalv = object_normal_at(intersection->obj, comps->point);
	comps->reflectv = vector_reflect(ray->direction, comps->normalv);
	if (vector_dot(comps->normalv, comps->eyev) < 0)
	{
		comps->inside = true;
		comps->normalv = vector_negate(comps->normalv);
	}
	else
		comps->inside = false;
	comps->over_point = tuple_add(comps->point,
			tuple_scale(comps->normalv, EPSILON, EPSILON, EPSILON));
}

int	compare_intersections(const void *a, const void *b)
{
	t_intersection	*ia;
	t_intersection	*ib;

	ia = (t_intersection *)a;
	ib = (t_intersection *)b;
	if (ia->t < ib->t)
		return (-1);
	else if (ia->t > ib->t)
		return (1);
	else
		return (0);
}

typedef struct s_intersectionAddParams
{
	t_intersection		**intersections;
	t_intersection_pair	*intersection_pair;
	t_object			*object;
	int					*count;
}	t_intersectionAddParams;

void	add_local_inter(t_intersectionAddParams *params)
{
	int	j;

	j = 0;
	while (j < params->intersection_pair->count)
	{
		(*(params->intersections))[*(params->count)
			+ j].obj = params->intersection_pair->obj;
		(*(params->intersections))[*(params->count)
			+ j].t = params->intersection_pair->t[j];
		(*(params->intersections))[*(params->count) + j].obj = params->object;
		j++;
	}
	*(params->count) += params->intersection_pair->count;
}

typedef struct s_processObjectParams
{
	t_world			*world;
	t_ray			*ray;
	t_intersection	**intersections;
	int				*capacity;
	int				*count;
	int				index;
}					t_processObjectParams;

void	process_object(t_processObjectParams *params)
{
	t_intersection_pair		local_inter;
	t_intersectionAddParams	add_params;

	object_intersect(&params->world->objects[params->index], params->ray, &local_inter);
	if (local_inter.count > 0)
	{
		if (*(params->count) + local_inter.count > *(params->capacity))
		{
			if (!intersection_realloc(params->intersections, *(params->count)
					+ local_inter.count, params->capacity))
				return ;
		}
		add_params = (t_intersectionAddParams){params->intersections,
			&local_inter, &params->world->objects[params->index],
			params->count};
		add_local_inter(&add_params);
	}
}

t_intersection	*intersect_world(t_world *world, t_ray *ray, int *count)
{
	int						capacity;
	t_intersection			*intersections;
	t_processObjectParams	params;
	int						i;

	i = 0;
	capacity = 10;
	intersections = malloc(capacity * sizeof(t_intersection));
	if (!intersections)
		return (NULL);
	*count = 0;
	while (i < world->object_count)
	{
		params = (t_processObjectParams){world, ray, &intersections, &capacity,
			count, i};
		process_object(&params);
		i++;
	}
	qsort(intersections, *count, sizeof(t_intersection), compare_intersections);
	return (intersections);
}
