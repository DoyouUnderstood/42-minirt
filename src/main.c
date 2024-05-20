/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:08:51 by alletond          #+#    #+#             */
/*   Updated: 2024/05/15 20:08:59 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../include/parser.h"
#include "object/test_shape.h"
#include <math.h>

void	error_exit(char *error_msg)
{
	printf("%s\n", error_msg);
	exit(1);
}

int	main(int argc, char *argv[])
{
	t_world	*world;

	(void)argc;
	(void)argv;
	world = NULL;
	if (argc != 2)
		return (0);
	world = read_and_parse(argv);
	mlx_initialisation(world);
	render(world);
	return (0);
}
