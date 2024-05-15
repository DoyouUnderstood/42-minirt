#include "../graphics/graphics.h"
#include "../include/parser.h"

int			parse_vec3(char *str, t_tuple *vec);

t_object	*create_cube(t_tuple center, double edge_length, t_color color,
				double reflectivity, t_pattern *pattern);

t_pattern	*set_pattern(char *part1, char *part2, char *part3)
{
	t_pattern	*pattern;
	t_color		start;
	t_color		end;

	pattern = NULL;
	rgb(part2, &start);
	rgb(part3, &end);
	start = convert_color_255_to_1(start.r, start.g, start.b);
	end = convert_color_255_to_1(end.r, end.g, end.b);
	if (!strcmp(part1, "gradient"))
		pattern = gradient_pattern_create(start, end);
	else if (!strcmp(part1, "checker"))
		pattern = checker_pattern_create(start, end);
	else if (!strcmp(part1, "ring"))
	{
		printf("Creating ring pattern\n");
		pattern = ring_pattern_create(start, end);
	}
	else if (!ft_strncmp(part1, "stripe", 6))
		pattern = stripe_pattern_create(start, end);
	return (pattern);
}

t_object	*parse_cylinder(char **parts, t_object *obj)
{
	double		reflectiv;
	t_cylinder	*cyl;
	t_color		color;
	t_pattern	*pattern;
	int			total_parts;

	reflectiv = 0;
	cyl = malloc(sizeof(t_cylinder));
	pattern = NULL;
	if (!parse_vec3(parts[1], &cyl->center))
		error_exit("Error with parsing center\n");
	if (!parse_vec3(parts[2], &cyl->axis))
		error_exit("Error with parsing orientation\n");
	if (!ft_atod(parts[3], &cyl->radius))
		error_exit("Error with parsing diameter\n");
	if (!ft_atod(parts[4], &cyl->height))
		error_exit("Error with parsing height\n");
	rgb(parts[5], &color);
	if (parts[6])
		reflectiv = atof(parts[6]);
	color = convert_color_255_to_1(color.r, color.g, color.b);
	total_parts = 0;
	while (parts[total_parts])
		total_parts++;
	if (total_parts >= 6 && parts[7] && parts[8] && parts[9])
	{
		printf("cylinder pattern\n");
		pattern = set_pattern(parts[7], parts[8], parts[9]);
	}
	obj = object_create_for_cylinder(cyl->center, cyl->radius, cyl->height,
			cyl->axis, color, reflectiv, pattern);
	free(cyl);
	return (obj);
}

// pe inverser pos et direction
t_camera	*parse_camera(char **parts, int hsize, int vsize)
{
	double		fov;
	t_camera	*camera;

	t_tuple position, direction;
	if (!parse_vec3(parts[1], &position))
		error_exit("Error with parsing position\n");
	if (!parse_vec3(parts[2], &direction))
		error_exit("Error with parsing direction\n");
	if (!ft_atod(parts[3], &fov) || !in_range(0, 70, fov))
		error_exit("Error with parsing or FOV out of range\n");
	camera = camera_create(hsize, vsize, fov, position, direction);
	if (!camera)
		error_exit("Failed to create camera\n");
	return (camera);
}

int	parse_point(char *str, t_tuple *vec)
{
	int		count;
	char	*next;

	count = 0;
	vec->x = ft_strtod(str);
	next = advance_to_next_component(&str);
	if (!next)
		return (0);
	count++;
	vec->y = ft_strtod(str);
	next = advance_to_next_component(&str);
	if (!next)
		return (0);
	count++;
	vec->z = ft_strtod(str);
	count++;
	vec->w = 1;
	return (count == 3);
}

t_object	*parse_plane(char **parts, t_object *obj)
{
	t_tuple		center;
	t_color		color;
	t_tuple 	direction;
	t_pattern	*pattern;
	int			total_parts;

	;
	pattern = NULL;
	if (!parse_vec3(parts[1], &center))
		error_exit("error with parsing\n");
	else
		rgb(parts[3], &color);
	if (!parse_vec3(parts[2], &direction))
		error_exit("error with parsing\n");
	color = convert_color_255_to_1(color.r, color.g, color.b);
	total_parts = 0;
	while (parts[total_parts])
		total_parts++;
	if (total_parts >= 6 && parts[4] && parts[5] && parts[6])
	{
		printf("PLANE pattern\n");
		pattern = set_pattern(parts[4], parts[5], parts[6]);
	}
	obj = object_create_for_plane(color, center, pattern, direction);
	return (obj);
}

t_obj_type	get_object_type(char *identifier)
{
	if (!strncmp(identifier, "sp", 2))
		return (SPHERE);
	else if (!strncmp(identifier, "pl", 2))
		return (PLANE);
	else if (!strncmp(identifier, "cy", 2))
		return (CYLINDER);
	else if (!strncmp(identifier, "cu", 2))
		return (CUBE);
	return (INVALID_TYPE);
}

t_object	*parse_cube(char **parts);

t_object	*create_cylinder_cap(t_cylinder *cylinder, t_color color);

void	parse_object(char **parts, t_world *world)
{
	t_object	*object;
	t_obj_type	type;

	object = NULL;
	type = get_object_type(parts[0]);
	if (type == SPHERE)
		object = parse_sphere(parts, object);
	if (type == PLANE)
		object = parse_plane(parts, object);
	if (type == CYLINDER)
	{
		object = parse_cylinder(parts, object);
		// t_object *obj = create_cylinder_cap((t_cylinder*)object,
				//object->shape->material->color);
		// world_add_object(world, obj);
	}
	if (type == CUBE)
		object = parse_cube(parts);
	world_add_object(world, object);
}

t_object	*parse_cube(char **parts)
{
	t_pattern	*pattern;
	t_tuple		center;
	double		edge_length;
	t_color		color;
	double		reflectivity;
	int			total_parts;
	t_object	*object;

	pattern = NULL;
	if (parts == NULL)
	{
		fprintf(stderr, "Input parts is null\n");
		return (NULL);
	}
	if (!parse_vec3(parts[1], &center))
	{
		fprintf(stderr, "Failed to parse center coordinates\n");
		return (NULL);
	}
	edge_length = atof(parts[2]);
	if (edge_length <= 0)
	{
		fprintf(stderr, "Invalid edge length\n");
		return (NULL);
	}
	rgb(parts[3], &color);
	reflectivity = atof(parts[4]);
	if (reflectivity < 0 || reflectivity > 1)
	{
		fprintf(stderr, "Invalid reflectivity value\n");
		return (NULL);
	}
	color = convert_color_255_to_1(color.r, color.g, color.b);
	total_parts = 0;
	while (parts[total_parts])
		total_parts++;
	if (total_parts > 6 && parts[5] && parts[6] && parts[7])
	{
		pattern = set_pattern(parts[5], parts[6], parts[7]);
	}
	object = create_cube(center, edge_length, color, reflectivity, pattern);
	if (object == NULL)
	{
		fprintf(stderr, "Failed to create cube\n");
		return (NULL);
	}
	return (object);
}

t_object	*parse_sphere(char **parts, t_object *object)
{
	t_tuple		center;
	t_pattern	*pattern;
	double		diameter;
	t_color		color;
	double		reflectiv;
	int			total_parts;

	pattern = NULL;
	reflectiv = 0;
	if (!parse_vec3(parts[1], &center))
		error_exit("error with parsing\n");
	if (!ft_atod(parts[2], &diameter))
		error_exit("error with parsing\n");
	rgb(parts[3], &color);
	if (parts[4])
		reflectiv = atof(parts[4]);
	color = convert_color_255_to_1(color.r, color.g, color.b);
	total_parts = 0;
	while (parts[total_parts])
		total_parts++;
	if (total_parts >= 6 && parts[5] && parts[6] && parts[7])
	{
		printf("SPHERE : part1: %s, part2: %s, part3: %s\n", parts[5], parts[6],
			parts[7]);
		printf("sphere pattern \n");
		pattern = set_pattern(parts[5], parts[6], parts[7]);
	}
	object = object_create_for_sphere(center, diameter, color, reflectiv,
			pattern);
	return (object);
}

t_light	*parse_light(char **parts)
{
	t_tuple pos;
	t_color color;
	t_light *light = NULL;
	double diffuse;
	if (!parse_vec3(parts[1], &pos))
		error_exit("error with parsing\n");
	if (!ft_atod(parts[2], &diffuse))
		error_exit("error with parsing\n");
	if (!valid_bright(diffuse))
		error_exit("error with parsing\n");
	rgb(parts[3], &color);
	color = convert_color_255_to_1(color.r, color.g, color.b);
	light = light_create(color, pos, diffuse);
	return (light);
}