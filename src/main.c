/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:08:51 by alletond          #+#    #+#             */
/*   Updated: 2024/05/21 18:29:18 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "functions.h"

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
