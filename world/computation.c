/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltd <ltd@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:17:31 by ltd               #+#    #+#             */
/*   Updated: 2024/05/15 17:29:16 by ltd              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../include/mathematique.h"
#include "../include/shape.h"
#include "../lib/libft/libft.h"
#include "../object/test_shape.h"
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
	comps->normalv = normal_at_shape(intersection->obj, comps->point);
	comps->reflectv = reflect(ray->direction, comps->normalv);
	if (vector_dot(comps->normalv, comps->eyev) < 0)
	{
		comps->inside = true;
		comps->normalv = vector_negate(comps->normalv);
	}
	else
		comps->inside = false;
	comps->over_point = tuple_add(comps->point, vector_multiply(comps->normalv,
				EPSILON));
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
	t_intersection	**intersections;
	t_intersection	*local_intersections;
	int				local_count;
	t_object		*object;
	int				*count;
}					t_intersectionAddParams;

void	add_local_inter(t_intersectionAddParams *params)
{
	int	j;

	j = 0;
	while (j < params->local_count)
	{
		(*(params->intersections))[*(params->count)
			+ j] = params->local_intersections[j];
		(*(params->intersections))[*(params->count) + j].obj = params->object;
		j++;
	}
	*(params->count) += params->local_count;
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
	int						local_count;
	t_intersection			*local_inter;
	t_intersectionAddParams	add_params;

	local_count = 0;
	local_inter = intersect_shape(params->world->objects[params->index],
			params->ray, &local_count);
	if (local_count > 0)
	{
		if (*(params->count) + local_count > *(params->capacity))
		{
			if (!realoc_inter(params->intersections, *(params->count)
					+ local_count, params->capacity))
			{
				free(local_inter);
				return ;
			}
		}
		add_params = (t_intersectionAddParams){params->intersections,
			local_inter, local_count, params->world->objects[params->index],
			params->count};
		add_local_inter(&add_params);
	}
	free(local_inter);
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
