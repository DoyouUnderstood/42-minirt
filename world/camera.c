#include "../include/main.h"
#include "../include/mathematique.h"
#include "../include/shape.h"
#include <math.h>


t_camera *camera_create(int hsize, int vsize, float fov_degrees, t_tuple position, t_tuple direction) 
{
    if (direction.x == 0 && direction.y == 0 && direction.z == 0) {
        fprintf(stderr, "Invalid camera direction vector.\n");
        return NULL;
    }

    t_camera *cam = malloc(sizeof(t_camera));
    if (!cam) {
        perror("Failed to allocate memory for camera");
        return NULL;
    }

    cam->hsize = hsize;
    cam->vsize = vsize;
    cam->fov = fov_degrees * M_PI / 180.0;
    cam->position = position;
    cam->direction = direction;

    cam->transform = view_transform(position, direction, vector_create(0, 1, 0));

    float half_view = tan(cam->fov / 2.0);
    float aspect = (float)cam->hsize / (float)cam->vsize;
    if (aspect >= 1) {
        cam->half_width = half_view;
        cam->half_height = half_view / aspect;
    } else {
        cam->half_width = half_view * aspect;
        cam->half_height = half_view;
    }

    cam->pixel_size = (cam->half_width * 2) / cam->hsize;
    return cam;
}
