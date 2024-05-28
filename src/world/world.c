/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:25:48 by ltd               #+#    #+#             */
/*   Updated: 2024/05/28 11:48:39 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"
#include "intersection.h"
#include "libft.h"
#include "ray.h"

#include <stdlib.h>

void	world_init(t_world *world)
{
	world->object_count = 0;
	ft_memset(&world->objects, 0, sizeof(world->objects));
}

void	world_intersect(t_world *world, t_ray *ray, t_intersection_arr *inter)
{
	int	i;

	i = 0;
	while (i < world->object_count)
	{
		object_intersect(&world->objects[i], ray, inter);
		i++;
	}
	intersection_arr_sort(inter);
}

char	*world_builder_add_object(t_world_builder *builder, t_object *object)
{
	if (builder->world->object_count >= MAX_OBJECTS)
		return ("Too many objects in rt file (max 30)\n");
	builder->world->objects[builder->world->object_count++] = *object;
	return (NULL);
}

char	*world_builder_build(t_world_builder *builder)
{
	if (!builder->resolution_set)
		return ("No resolution was set");
	if (!builder->camera_set)
		return ("No camera was set");
	if (!builder->ambient_light_set)
		return ("No ambient light was set");
	if (!builder->light_set)
		return ("No light set");
	if (builder->world->object_count == 0)
		return ("No object was set");
	builder->camera_data.hsize = builder->world->hsize;
	builder->camera_data.vsize = builder->world->vsize;
	return (camera_init(&builder->world->camera, &builder->camera_data));
}
