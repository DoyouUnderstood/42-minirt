/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:28:06 by ltd               #+#    #+#             */
/*   Updated: 2024/05/21 11:13:30 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "mathematique.h"
#include "shape_old.h"

#include <math.h>
#include <stdio.h>

void	setup_thread_data(t_threadSetupParams *params)
{
	params->thread_data->mlx = params->world->mlx;
	params->thread_data->world = params->world;
	params->thread_data->camera = params->world->camera;
	params->thread_data->inverse_transform = params->inverse_transform;
	params->thread_data->start_y = params->index * params->segment_height;
	if (params->index == params->num_threads - 1)
		params->thread_data->end_y = params->world->camera->vsize;
	else
	{
		params->thread_data->end_y = (params->index + 1)
			* params->segment_height;
	}
}
