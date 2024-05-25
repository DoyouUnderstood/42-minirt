/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:08:51 by alletond          #+#    #+#             */
/*   Updated: 2024/05/25 05:48:05 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "functions.h"

#include <math.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	t_world	world;

	world_init(&world);
	if (argc != 2)
		return (0);
	parse_rt_file(argv[1], &world);
	mlx_initialisation(&world);
	render(&world);
	return (0);
}
