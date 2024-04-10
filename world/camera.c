#include "../include/main.h"

#include "../include/graphics.h"
#include "../include/mathematique.h"
#include "../include/shape.h"
#include <math.h>

t_camera camera_create(int hsize, int vsize, float fov) 
{
    t_camera cam;
    cam.hsize = hsize;
    cam.vsize = vsize;
    cam.fov = fov;
    cam.transform = matrix_init_identity();

    float half_view = tan(cam.fov / 2.0);
    float aspect = (float)cam.hsize / (float)cam.vsize;

    if (aspect >= 1) {
        cam.half_width = half_view;
        cam.half_height = half_view / aspect;
    } else {
        cam.half_width = half_view * aspect;
        cam.half_height = half_view;
    }

    cam.pixel_size = (cam.half_width * 2) / cam.hsize;

    return cam;
}

t_ray ray_for_pixel(const t_camera *camera, const t_matrix *inverse_transform, int px, int py) 
{
    double xoffset = (px + 0.5) * camera->pixel_size;
    double yoffset = (py + 0.5) * camera->pixel_size;
    double world_x = camera->half_width - xoffset;
    double world_y = camera->half_height - yoffset; 
    t_tuple pixel = matrix_multiply_by_tuple(*inverse_transform, (t_tuple){world_x, world_y, -1, 1});
    t_tuple origin = matrix_multiply_by_tuple(*inverse_transform, (t_tuple){0, 0, 0, 1});
    t_tuple direction = vector_normalize(tuple_subtract(pixel, origin));

    return ((t_ray){origin, direction});
}
