/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:40:35 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/22 17:12:37 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "parser.h"

char	*parse_resolution(t_parser *parser, t_world *world)
{
	if (!parser_skip_spaces(parser))
		return ("Resolution: Missing space");
	if (!parser_consume_int(parser, &world->vsize) || world->vsize < 1)
		return ("Resolution: Invalid height");
	parser_skip_spaces(parser);
	if (!parser_consume_int(parser, &world->hsize) || world->hsize < 1)
		return ("Resolution: Invalid width");
	parser_skip_spaces(parser);
	if (!parser_match_char(parser, '\n') && !parser_at_end(parser))
		return ("Resolution: Invalid data at end of line");
	return (NULL);
}

char	*parse_ambient(t_parser *parser, t_world *world)
{
	t_amb_light	*amb_light;
	char		*error;

	amb_light = malloc(sizeof(t_amb_light));
	if (!amb_light)
		return ("Ambient light: malloc error");
	if (!parser_skip_spaces(parser))
		return (parser_handle_error(amb_light, "Ambient light: Missing space after A"));
	if (!parser_consume_double(parser, &amb_light->ambient))
		return (parser_handle_error(amb_light, "Ambient light: Invalid intensity"));
	if (!parser_skip_spaces(parser))
		return (parser_handle_error(amb_light, "Ambient light: Missing space after intensity"));
	error = parse_color(parser, &amb_light->color);
	if (error)
		return (parser_handle_error(amb_light, error));
	world->amb = amb_light;
	return (NULL);
}