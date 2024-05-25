/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 05:42:23 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 05:43:22 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include "parser.h"
# include "world.h"

/* ------------------ WORLD CHARACTERISTICS --------------------- */

char	*parse_resolution(t_parser *parser, t_world *world);
char	*parse_ambient(t_parser *parser, t_world *world);
char	*parse_camera(t_parser *parser, t_world *world);
char	*parse_light(t_parser *parser, t_world *world);

/* ------------------ OBJECTS --------------------- */

char	*parse_sphere(t_parser *parser, t_world *world);
char	*parse_cylinder(t_parser *parser, t_world *world);
char	*parse_cube(t_parser *parser, t_world *world);
char	*parse_plane(t_parser *parser, t_world *world);
char	*parse_material(t_parser *parser, t_material *material);

#endif