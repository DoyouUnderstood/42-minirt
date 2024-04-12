#ifndef INIT_H
#define INIT_H

#include "../include/shape.h"

typedef struct s_camera t_camera;
typedef struct s_mlx t_mlx;

void world_init(t_world **world, t_camera **camera);
void mlx_initialisation(t_mlx **mlx);
void    world_fill(t_world *world);

#endif