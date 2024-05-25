/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:25:48 by ltd               #+#    #+#             */
/*   Updated: 2024/05/25 08:02:22 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "world.h"

#include <stdlib.h>

void	world_init(t_world *world)
{
	world->object_count = 0;
	ft_memset(&world->objects, 0, sizeof(world->objects));
}

char	*world_init_resolution(t_world *world, int width, int height)
{
	static int	count = 0;

	if (count > 0)
		return ("Resolution can only be initialized once.");
	count++;
	if (width < 1 || height < 1)
		return ("Resolution width and height must be positive numbers");
	world->hsize = width;
	world->vsize = height;
	return (NULL);
}

char	*world_init_camera(t_world *world, t_camera_data *data)
{
	static int	count = 0;

	if (count > 0)
		return ("Camera can only be initialized once.");
	count++;
	return (camera_init(&world->camera, data));
}

char	*world_init_light(t_world *world, t_light *data)
{
	char	*error;

	error = light_validate(data);
	if (!error)
		world->light = *data;
	return (error);
}

char	*world_init_ambient(t_world *world, t_amb_light *data)
{
	char	*error;

	error = amb_light_validate(data);
	if (!error)
		world->amb = *data;
	return (error);
}

char	*world_validate(t_world *world)
{
	// Validate existence of a camera
	// Validate existence of a ambient light
	// Validate existence of a light
	if (!world->objects)
		return ("Erreur : Aucune forme géométrique définie dans le fichier.\n");
	return (NULL);
}

// add object into world.
char	*world_add_object(t_world *world, t_object *object)
{
	if (world->object_count >= MAX_OBJECTS)
		return ("Too many objects in rt file (max 30)\n");
	world->objects[world->object_count++] = *object;
	return (NULL);
}
