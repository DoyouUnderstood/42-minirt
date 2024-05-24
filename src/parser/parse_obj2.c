/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:38:13 by ltd               #+#    #+#             */
/*   Updated: 2024/05/24 13:27:53 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include "cube.h"
#include "ft_error.h"
#include "functions.h"
#include "libft.h"
#include "cube.h"

#include "parser.h"

t_obj_type	get_object_type(char *identifier)
{
	if (!ft_strncmp(identifier, "pl", 2))
		return (PLANE);
	return (INVALID_TYPE);
}

void	parse_object(char **parts, t_world *world)
{
	t_object	*object;
	t_obj_type	type;

	object = NULL;
	type = get_object_type(parts[0]);
	if (type == PLANE)
		object = parse_plane(parts, object);
	world_add_object(world, object);
}
