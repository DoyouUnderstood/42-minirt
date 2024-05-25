/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:08:05 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 05:12:02 by erabbath         ###   ########.fr       */
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
# include "plane.h"


t_world	*parse_rt_file(char *filename);

char	*parse_material(t_parser *parser, t_material *material);

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

char	*parse_sphere(t_parser *parser, t_world *world);
char	*parse_cylinder(t_parser *parser, t_world *world);
char	*parse_cube(t_parser *parser, t_world *world);
char	*parse_plane(t_parser *parser, t_world *world);

#endif