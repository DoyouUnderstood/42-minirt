/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:40:02 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/21 18:20:29 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"
#include "parser.h"
#include "get_next_line.h"
#include "ft_printf.h"
#include "libft.h"
#include "world.h"
#include "functions.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

char	*file_to_str(const char *filename)
{
	int			fd;
	struct stat	st;
	char		*file_content;
	ssize_t		bytes_read;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_exit("error open\n");
	if (fstat(fd, &st) == -1)
		error_exit("error fstat\n");
	file_content = malloc(st.st_size + 1);
	bytes_read = read(fd, file_content, st.st_size);
	if (bytes_read == -1)
	{
		perror("Error reading file");
		free(file_content);
		close(fd);
		return (NULL);
	}
	file_content[bytes_read] = '\0';
	close(fd);
	return (file_content);
}

void	verify_world(t_world *world)
{
	if (!world->camera)
		fprintf(stderr, "Erreur : Aucune caméra définie dans le fichier.\n");
	if (!world->amb)
		fprintf(stderr,
			"Erreur : Aucune lumière ambiante définie dans le fichier.\n");
	if (!world->light)
		fprintf(stderr,
			"Erreur : Aucune lumière principale définie dans le fichier.\n");
	if (!world->objects)
		fprintf(stderr,
			"Erreur : Aucune forme géométrique définie dans le fichier.\n");
	if (!world->camera || !world->amb || !world->light || !world->objects)
	{
		fprintf(stderr,
			"Échec de chargement du monde : des composants sont manquants.\n");
		exit(EXIT_FAILURE);
	}
}

// parse the whole .rt
t_world	*parse(char **str, t_world *world)
{
	char	**ptr;
	int		i;

	i = 0;
	while (str[i])
	{
		ptr = ft_split(str[i], ' ');
		if (!ft_strncmp(ptr[0], "R", ft_strlen(ptr[0])))
		{
			world->vsize = atoi(ptr[1]);
			world->hsize = atoi(ptr[2]);
		}
		if (!ft_strncmp(ptr[0], "A", ft_strlen(ptr[0])))
			world->amb = parse_amb(ptr);
		if (!ft_strncmp(ptr[0], "C", ft_strlen(ptr[0])))
			world->camera = parse_camera(ptr, world->hsize, world->vsize);
		else if (!strncmp(ptr[0], "L", ft_strlen(ptr[0])))
			world->light = parse_light(ptr);
		else
			parse_object(ptr, world);
		free_split(ptr);
		i++;
	}
	verify_world(world);
	return (world);
}

// read .rt and fill and return the whole world.
t_world	*read_and_parse(char **argv)
{
	t_world	*scene;
	char	**ptr;
	char	*str;
	int		i;

	i = 0;
	str = file_to_str(argv[1]);
	ptr = ft_split(str, '\n');
	scene = world_create();
	scene = parse(ptr, scene);
	free(str);
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (scene);
}
