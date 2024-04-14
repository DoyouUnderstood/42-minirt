#ifndef RAY_H
#define RAY_H

#include "mathematique.h"
#include "minilibx.h"
// #include "shape.h"
// #include "graphics.h"

typedef struct s_mlx t_mlx;
typedef struct s_sphere t_sphere;

typedef struct s_ray 
{
    t_tuple origin;
    t_tuple direction;
} t_ray;

// =========== RAY ============

t_ray ray_create(t_tuple origin, t_tuple direction);
t_ray   ray_transform(t_matrix mat, t_ray ray);
// void    ray_throw(t_mlx *mlx, t_sphere *sphere, t_light *light);
t_tuple t_point_position(const t_ray *ray, double t);
t_ray   ray_init(t_mlx *mlx, int x, int y, double projection_plane_z);
void    print_ray(t_ray ray);

#endif