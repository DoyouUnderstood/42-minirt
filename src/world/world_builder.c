/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_builder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 20:19:30 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/26 21:08:10 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

#include <stdlib.h>

void	world_builder_init(t_world_builder *builder, t_world *world)
{
	world_init(world);
	builder->world = world;
	builder->resolution_set = false;
	builder->camera_set = false;
	builder->ambient_light_set = false;
	builder->light_set = false;
}

char	*world_builder_set_resolution(t_world_builder *builder, int width,
	int height)
{
	if (builder->resolution_set)
		return ("Resolution can only be set once");
	builder->resolution_set = true;
	if (width < 1 || height < 1)
		return ("Resolution width and height must be positive numbers");
	builder->world->hsize = width;
	builder->world->vsize = height;
	return (NULL);
}

char	*world_builder_set_camera(t_world_builder *builder,
	t_camera_data *data)
{
	if (builder->camera_set)
		return ("Camera can only be set once");
	builder->camera_set = true;
	builder->camera_data = *data;
	return (NULL);
}

char	*world_builder_set_ambient(t_world_builder *builder,
	t_amb_light *data)
{
	char	*error;

	if (builder->ambient_light_set)
		return ("Ambient light can only be set once");
	builder->ambient_light_set = true;
	error = amb_light_validate(data);
	if (!error)
		builder->world->amb = *data;
	return (error);
}

char	*world_builder_set_light(t_world_builder *builder,
	t_light *data)
{
	char	*error;

	if (builder->light_set)
		return ("Light can only be set once");
	builder->light_set = true;
	error = light_validate(data);
	if (!error)
		builder->world->light = *data;
	return (error);
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
