#include "../include/main.h"
#include "../include/mathematique.h"
#include "../include/shape.h"
#include "../object/test_shape.h"
#include "graphics.h"

t_color	color_at(t_world *world, t_ray *ray, int remaining)
{
	int				count;
	t_intersection	*intersections;
	t_intersection	*hit_inter;
	t_computations	comput;
	t_color			color;

	count = 0;
	intersections = intersect_world(world, ray, &count);
	if (!intersections || count == 0)
	{
		free(intersections);
		return (color_multiply_scalar(world->amb->color, world->amb->ambient));
	}
	hit_inter = hit(intersections, count);
	if (!hit_inter)
	{
		free(intersections);
		return (color_multiply_scalar(world->amb->color, world->amb->ambient));
	}
	prepare_computations(&comput, hit_inter, ray);
	color = shade_hit(world, &comput, remaining);
	free(intersections);
	return (color);
}

t_color	shade_hit(t_world *world, t_computations *comps, int remaining)
{
	bool	in_shadow;
	t_color	surface;
	t_color	reflected;

	in_shadow = is_shadowed(world, comps->over_point);
	surface = lighting(comps->object->shape->material, comps->object,
			world->light, &comps->over_point, &comps->eyev, &comps->normalv,
			in_shadow);
	reflected = reflected_color(world, comps, remaining);
	return (color_add(surface, reflected));
}
