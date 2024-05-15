#include "../include/main.h"
#include "../include/mathematique.h"
#include "../include/shape.h"
#include "../lib/libft/libft.h"
#include "../object/test_shape.h"
#define EPSILON 0.00001

void	prepare_computations(t_computations *comps,
		const t_intersection *intersection, const t_ray *ray)
{
	if (comps == NULL)
		return ;
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
	}
	else
		comps->inside = false;
	comps->over_point = tuple_add(comps->point, vector_multiply(comps->normalv,
				EPSILON));
}

int	compare_intersections(const void *a, const void *b)
{
	t_intersection	*ia;
	t_intersection	*ib;

	ia = (t_intersection *)a;
	ib = (t_intersection *)b;
	if (ia->t < ib->t)
		return (-1);
	else if (ia->t > ib->t)
		return (1);
	else
		return (0);
}


typedef struct {
    t_intersection **intersections;
    t_intersection *local_intersections;
    int local_count;
    t_object *object;
    int *count;
} IntersectionAddParams;


void add_local_inter(IntersectionAddParams *params) {
    for (int j = 0; j < params->local_count; j++) {
        (*(params->intersections))[*(params->count) + j] = params->local_intersections[j];
        (*(params->intersections))[*(params->count) + j].obj = params->object;
    }
    *(params->count) += params->local_count;
}


/**
 * Computes all intersections of a given ray with every object in the world.
 * Allocates and returns a list of sort intersections,
 */

bool realloc_intersections(t_intersection **intersections, int required_capacity, int *capacity) {
    while (required_capacity > *capacity) {
        *capacity *= 2;
    }
    t_intersection *temp = realloc(*intersections, (*capacity) * sizeof(t_intersection));
    if (!temp) {
        return false;
    }
    *intersections = temp;
    return true;
}

void process_object(t_world *world, t_ray *ray, t_intersection **intersections, int *capacity, int *count, int i) {
    int local_count = 0;
    t_intersection *local_inter = intersect_shape(world->objects[i], ray, &local_count);
    if (local_count > 0) {
        if (*count + local_count > *capacity) {
            if (!realloc_intersections(intersections, *count + local_count, capacity)) {
                free(local_inter);
                return;
            }
        }
        IntersectionAddParams params = {intersections, local_inter, local_count, world->objects[i], count};
        add_local_inter(&params);
    }
    free(local_inter);
}


t_intersection *intersect_world(t_world *world, t_ray *ray, int *count) {
    int capacity = 10;
    t_intersection *intersections = malloc(capacity * sizeof(t_intersection));
    if (!intersections) return NULL;
    
    *count = 0;
    for (int i = 0; i < world->object_count; i++) {
        process_object(world, ray, &intersections, &capacity, count, i);
    }
    qsort(intersections, *count, sizeof(t_intersection), compare_intersections);
    return intersections;
}
