#include "../include/main.h"

#include "../include/graphics.h"
#include "../include/mathematique.h"
#include "../include/shape.h"
#include "../object/test_shape.h"
#define EPSILON 0.00001

void prepare_computations(t_computations *comps, const t_intersection *intersection, const t_ray *ray) 
{
    if (comps == NULL) 
        return;
    comps->t = intersection->t;
    comps->object = intersection->obj;
    comps->point = t_point_position(ray, intersection->t);
    comps->eyev = vector_negate(ray->direction);
    comps->normalv = normal_at_shape(intersection->obj, comps->point);
    comps->reflectv = reflect(ray->direction, comps->normalv);
    
    if (vector_dot(comps->normalv, comps->eyev) < 0)
    {
        comps->inside = true;
        comps->normalv = vector_negate(comps->normalv);
    } else
        comps->inside = false;
    comps->over_point = tuple_add(comps->point, vector_multiply(comps->normalv, EPSILON));
}

int compare_intersections(const void* a, const void* b) 
{
    t_intersection* ia = (t_intersection*)a;
    t_intersection* ib = (t_intersection*)b;
    if (ia->t < ib->t) 
        return -1;
    else if (ia->t > ib->t) 
        return 1;
    else return 0;
}

t_intersection* intersect_world(t_world* world, t_ray* ray, int* count) {
    *count = 0;
    int capacity = 10;
    t_intersection* intersections = malloc(capacity * sizeof(t_intersection));
    if (!intersections) {
        return NULL;
    }
    for (int i = 0; i < world->object_count; i++) 
    {
        int local_count = 0;
        t_intersection* local_intersections = intersect_shape(world->objects[i], ray, &local_count);
        if (local_count > 0) {
            while (*count + local_count > capacity) {
                capacity *= 2;
                intersections = realloc(intersections, capacity * sizeof(t_intersection));
                if (!intersections) {
                    free(local_intersections);
                    return NULL;
                }
            }
            for (int j = 0; j < local_count; j++) {
                intersections[*count + j] = local_intersections[j];
                intersections[*count + j].obj = world->objects[i];
            }
            *count += local_count;
        }
        if (local_intersections != NULL) {
            free(local_intersections);
        }
    }

    qsort(intersections, *count, sizeof(t_intersection), compare_intersections);

    return intersections;
}

