/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:08:05 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/15 16:08:06 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../lib/GNL/get_next_line.h"
# include "../lib/ft_printf/ft_printf.h"
# include "../lib/libft/libft.h"
# include "init.h"
# include "shape.h"
# include <stdbool.h>

t_amb_light	*parse_amb(char **str);
bool		in_range(double start, double end, double value);
char		*advance_to_next_component(char **str);
int			parse_vec3(char *str, t_tuple *vec);
t_camera	*parse_camera(char **parts, int hsize, int vsize);
t_light		*parse_light(char **parts);
void		parse_object(char **parts, t_world *world);
t_object	*parse_plane(char **parts, t_object *obj);
t_object	*parse_sphere(char **parts, t_object *object);
bool		valid_bright(double bright);
t_world		*read_and_parse(char **argv);
void		free_split(char **parts);
void		rgb(char *str, t_color *color);

#endif