/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:25:48 by ltd               #+#    #+#             */
/*   Updated: 2024/05/25 06:22:19 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

#include <stdlib.h>

void	world_init(t_world *world)
{
	int		i;

	i = 0;
	world->light = NULL;
	world->object_count = 0;
	while (i < MAX_OBJECTS)
		world->objects[i++] = NULL;
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

char	*world_validate(t_world *world)
{
	// Validate existence of a camera
	if (!world->amb)
		return ("Erreur : Aucune lumière ambiante définie dans le fichier.\n");
	if (!world->light)
		return ("Erreur : Aucune lumière principale définie dans le fichier.\n");
	if (!world->objects)
		return ("Erreur : Aucune forme géométrique définie dans le fichier.\n");
	return (NULL);
}

// add object into world.
char	*world_add_object(t_world *world, t_object *object)
{
	if (object == NULL)
		return (NULL);
	if (world->object_count >= MAX_OBJECTS)
		return ("To many objects in rt file (max 30)\n");
	world->objects[world->object_count++] = object;
	return (NULL);
}
