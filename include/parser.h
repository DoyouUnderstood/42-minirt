/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:08:05 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/22 17:04:33 by erabbath         ###   ########.fr       */
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

# include "get_next_line.h"
# include "ft_printf.h"
# include "libft.h"
# include <stdbool.h>

t_world	*read_and_parse(char *filename);

// Utils
char	*parser_handle_error(void *p, char *msg);
char	*parse_color(t_parser *parser, t_color *color);
char	*parse_tuple(t_parser *parser, t_tuple *tuple,
			t_tuple (*tuple_creator_f)(double x, double y, double z));

// Parsers
char	*parse_resolution(t_parser *parser, t_world *world);
char	*parse_ambient(t_parser *parser, t_world *world);


bool		in_range(double start, double end, double value);
char		*advance_to_next_component(char **str);
int			parse_vec3(char *str, t_tuple *vec);
t_camera	*parse_cam(char **parts, int hsize, int vsize);
t_light		*parse_light(char **parts);
void		parse_object(char **parts, t_world *world);
t_object	*parse_plane(char **parts, t_object *obj);
t_object	*parse_sphere(char **parts, t_object *object);
bool		valid_bright(double bright);
void		free_split(char **parts);
void		rgb(char *str, t_color *color);
double		validate_reflectivity(double value);
char		*require_str(char *s);

#endif