#ifndef INIT_H
#define INIT_H

typedef struct s_world t_world;
typedef struct s_camera t_camera;
typedef struct s_mlx t_mlx;

void world_init(t_world **world, t_camera **camera);
void world_fill(t_world *world);
void mlx_initialisation(t_mlx **mlx);


#endif // INIT_H
