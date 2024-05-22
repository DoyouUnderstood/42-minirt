/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:41:43 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/22 16:54:31 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "parser.h"

char	*parser_handle_error(void *p, char *msg)
{
	free(p);
	return (msg);
}

char	*parse_color(t_parser *parser, t_color *color)
{
	int	r;
	int	g;
	int	b;

	if (!parser_consume_int(parser, &r) || r < 0 || r > 255)
		return ("Ambient light: Invalid red color");
	if (!parser_match_char(parser, ','))
		return ("Ambient light: Missing comma after red color");
	if (!parser_consume_int(parser, &g) || g < 0 || g > 255)
		return ("Ambient light: Invalid green color");
	if (!parser_match_char(parser, ','))
		return ("Ambient light: Missing comma");
	if (!parser_consume_int(parser, &b) || b < 0 || b > 255)
		return ("Ambient light: Invalid blue color");
	*color = color_from_rgb(r, g, b);
	return (NULL);
}

char	*parse_tuple(t_parser *parser, t_tuple *tuple,
	t_tuple (*tuple_creator_f)(double x, double y, double z))
{
	double	x;
	double	y;
	double	z;

	if (!parser_consume_double(parser, &x))
		return ("Invalid x coordinate");
	if (!parser_match_char(parser, ','))
		return ("Comma missing after x coordinate");
	if (!parser_consume_double(parser, &y))
		return ("Invalid y coordinate");
	if (!parser_match_char(parser, ','))
		return ("Comma missing after y coordinate");
	if (!parser_consume_double(parser, &z))
		return ("Invalid z coordinate");
	*tuple = tuple_creator_f(x, y, z);
	return (NULL);
}