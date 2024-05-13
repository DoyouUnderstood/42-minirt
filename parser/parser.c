#include "../lib/libft/libft.h"
#include "../lib/GNL/get_next_line.h"
#include "../lib/ft_printf/ft_printf.h"
#include "../include/init.h"
#include "../include/shape.h"
#include "../include/parser.h"
#include <fcntl.h>

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

// fill the .rt into string. 
// Need to replace stat for GNL before push. 
char *file_to_str(const char *filename)
{
    int fd;
    struct stat st;
    char *file_content;
    ssize_t bytes_read;
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return NULL;
    }
    if (fstat(fd, &st) == -1)
    {
        perror("Error getting file size");
        close(fd);
        return NULL;
    }
    file_content = malloc(st.st_size + 1);
    if (file_content == NULL)
    {
        perror("Memory allocation failed");
        close(fd);
        return NULL;
    }
    bytes_read = read(fd, file_content, st.st_size);
    if (bytes_read == -1)
    {
        perror("Error reading file");
        free(file_content);
        close(fd);
        return NULL;
    }
    file_content[bytes_read] = '\0';
    close(fd);
    return (file_content);
}


void verify_world(t_world *world) {
    if (!world->camera)
        fprintf(stderr, "Erreur : Aucune caméra définie dans le fichier.\n");
    if (!world->amb)
        fprintf(stderr, "Erreur : Aucune lumière ambiante définie dans le fichier.\n");
    if (!world->light)
        fprintf(stderr, "Erreur : Aucune lumière principale définie dans le fichier.\n");
    if (!world->objects)
        fprintf(stderr, "Erreur : Aucune forme géométrique définie dans le fichier.\n");

    if (!world->camera || !world->amb || !world->light || !world->objects) {
        fprintf(stderr, "Échec de chargement du monde : des composants essentiels sont manquants.\n");
        exit(EXIT_FAILURE);
    }
}


// parse the whole .rt
t_world *parse(char **str, t_world *world) 
{
    char **ptr;
    int i;
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
            world->camera = parse_camera(ptr, world->vsize, world->hsize);
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
t_world *read_and_parse(char **argv)
{
    t_world *scene;
    
    char *str = file_to_str(argv[1]);
    char **ptr = ft_split(str, '\n');
    scene = world_create();
    scene = parse(ptr, scene);
    free(str);
    int i = 0;
    while (ptr[i])
    {
        free(ptr[i]);
        i++;
    }
    free(ptr);
    return (scene);
}