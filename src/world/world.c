/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:25:48 by ltd               #+#    #+#             */
/*   Updated: 2024/05/25 05:55:22 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

#include <stdlib.h>

void	world_init(t_world *world)
{
	int		i;

	i = 0;
	world->light = NULL;
	world->camera = NULL;
	world->object_count = 0;
	while (i < MAX_OBJECTS)
		world->objects[i++] = NULL;
}

char	*world_validate(t_world *world)
{
	if (!world->camera)
		return ("Erreur : Aucune caméra définie dans le fichier.");
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
