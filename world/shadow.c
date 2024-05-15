#include "../include/main.h"
#include "../include/mathematique.h"
#include "../include/shape.h"
#include <math.h>

typedef struct s_shadow
{
	t_tuple			direction;
	double			distance;
	t_ray			shadow_ray;
	int				count;
	t_intersection	*intersections;
}					t_shadow;

bool	is_shadowed(t_world *world, const t_tuple point)
{
	t_shadow	shadow;
	bool		in_shadow;
	int			i;

	i = 0;
	if (world->light->intensity.r == 0 && world->light->intensity.g == 0
		&& world->light->intensity.b == 0)
		return (false);
	shadow.direction = tuple_subtract(world->light->pos, point);
	shadow.distance = tuple_magnitude(&shadow.direction);
	shadow.direction = vector_normalize(shadow.direction);
	shadow.shadow_ray = ray_create(point, shadow.direction);
	shadow.count = 0;
	shadow.intersections = intersect_world(world, &shadow.shadow_ray,
			&shadow.count);
	in_shadow = false;
	while (i < shadow.count)
	{
		if (shadow.intersections[i].t > 0
			&& shadow.intersections[i].t < shadow.distance)
		{
			in_shadow = true;
			break ;
		}
		i++;
	}
	free(shadow.intersections);
	return (in_shadow);
}
