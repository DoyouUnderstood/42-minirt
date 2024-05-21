/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:25:48 by ltd               #+#    #+#             */
/*   Updated: 2024/05/21 11:14:04 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "mathematique.h"
#include "shape_old.h"
#include "../object/test_shape.h"

#define MAX_OBJECTS 30

// add object into world.
void	world_add_object(t_world *world, t_object *object)
{
	if (object == NULL)
		return ;
	if (world->object_count < MAX_OBJECTS)
	{
		world->objects[world->object_count++] = object;
	}
	else
	{
		error_exit("faut enlever des objects l'ami!\n");
	}
}

// initialisation of world.
t_world	*world_create(void)
{
	t_world	*w;
	int		i;

	i = 0;
	w = malloc(sizeof(t_world));
	if (!w)
		return (NULL);
	w->light = NULL;
	w->camera = NULL;
	w->object_count = 0;
	w->objects = malloc(MAX_OBJECTS * sizeof(t_object *));
	if (!w->objects)
	{
		free(w);
		return (NULL);
	}
	while (i < MAX_OBJECTS)
		w->objects[i++] = NULL;
	return (w);
}

// annihilation of world.
void	world_destroy(t_world *world)
{
	int	i;

	i = 0;
	if (!world)
		return ;
	while (i < world->object_count)
	{
		free(world->objects[i]);
		i++;
	}
	free(world->objects);
	free(world);
}
