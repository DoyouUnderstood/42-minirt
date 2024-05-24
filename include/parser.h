/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:08:05 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/24 16:01:55 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "ft_parser.h"
# include "light.h"
# include "tuple.h"
# include "camera.h"
# include "object.h"
# include "world.h"
# include "sphere.h"
# include "cylinder.h"
# include "cube.h"
# include "plane.h"

# include "get_next_line.h"
# include "ft_printf.h"
# include "libft.h"
# include <stdbool.h>

/* ------------------ MAIN FUNCTION -------------------- */

t_world	*parse_rt_file(char *filename);

/* ------------------ UTILITIES -------------------- */
char	*parser_handle_error(void *p, char *msg);
bool	parser_valid_intensity(double intensity);
char	*parse_color(t_parser *parser, t_color *color);
char	*parse_tuple(t_parser *parser, t_tuple *tuple,
			t_tuple (*tuple_creator_f)(double x, double y, double z));
char	*parse_reflectivity(t_parser *parser, double *reflectivity);

/* ------------------ PATTERN -------------------- */

typedef struct s_parser_pattern
{
	t_pattern	*(*pattern_f)(t_color c1, t_color c2);
	t_color_255	color1;
	t_color_255	color2;
}	t_parser_pattern;

char	*parse_pattern(t_parser *parser, t_pattern **pattern);

/* ------------------ RESOLUTION -------------------- */

char	*parse_resolution(t_parser *parser, t_world *world);

/* ------------------ AMBIENT LIGHT --------------------- */

typedef struct s_parser_ambient
{
	double		intensity;
	t_color_255	color;
}	t_parser_ambient;

char	*parse_ambient(t_parser *parser, t_world *world);

/* ------------------ CAMERA --------------------- */

typedef struct s_parser_camera
{
	t_tuple	position;
	t_tuple	direction;
	double	fov;
}	t_parser_camera;

char	*parse_camera(t_parser *parser, t_world *world);

/* ------------------ POINT LIGHT --------------------- */

typedef struct s_parser_light
{
	t_tuple		position;
	double		intensity;
	t_color_255	color;
}	t_parser_light;

char	*parse_light(t_parser *parser, t_world *world);

/* ------------------ SPHERE --------------------- */

typedef struct s_parser_sphere
{
	t_sphere_data	sphere;
	t_color_255		color;
	double			reflectivity;
	t_pattern		*pattern;
}	t_parser_sphere;

char	*parse_sphere(t_parser *parser, t_world *world);

/* ------------------ CYLINDER --------------------- */

typedef struct s_parser_cylinder
{
	t_cylinder_data	cylinder;
	t_color_255		color;
	double			reflectivity;
	t_pattern		*pattern;
}	t_parser_cylinder;

char	*parse_cylinder(t_parser *parser, t_world *world);

/* ------------------ CUBE --------------------- */

typedef struct s_parser_cube
{
	t_cube_data		cube;
	t_color_255		color;
	double			reflectivity;
	t_pattern		*pattern;
}	t_parser_cube;

char	*parse_cube(t_parser *parser, t_world *world);

/* ------------------ PLANE --------------------- */

typedef struct s_parser_plane
{
	t_plane_data		plane;
	t_color_255		color;
	double			reflectivity;
	t_pattern		*pattern;
}	t_parser_plane;

char	*parse_plane(t_parser *parser, t_world *world);

// OLD
bool		in_range(double start, double end, double value);
char		*advance_to_next_component(char **str);
int			parse_vec3(char *str, t_tuple *vec);
void		parse_object(char **parts, t_world *world);
bool		valid_bright(double bright);
void		free_split(char **parts);
void		rgb(char *str, t_color *color);
double		validate_reflectivity(double value);
char		*require_str(char *s);

#endif