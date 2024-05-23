/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:41:43 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/23 11:02:29 by erabbath         ###   ########.fr       */
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

	if (!parser_match(parser, "%d%_,%_%d%_,%_%d", &r, &g, &b))
		return ("Invalid color format");
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return ("Invalid color values");
	*color = color_from_rgb(r, g, b);
	return (NULL);
}

char	*parse_tuple(t_parser *parser, t_tuple *tuple,
	t_tuple (*tuple_creator_f)(double x, double y, double z))
{
	double	x;
	double	y;
	double	z;

	if (!parser_match(parser, "%f%_,%_%f%_,%_%f", &x, &y, &z))
		return ("Invalid tuple format");
	*tuple = tuple_creator_f(x, y, z);
	return (NULL);
}

char	*parse_pattern(t_parser *parser, t_pattern **pattern)
{
	t_pattern	*(*pattern_f)(t_color c1, t_color c2);
	t_color		color1;
	t_color		color2;

	pattern_f = NULL;
	*pattern = NULL;
	if (parser_match(parser, " gradient "))
		pattern_f = gradient_pattern_create;
	else if (parser_match(parser, " checker "))
		pattern_f = checker_pattern_create;
	else if (parser_match(parser, " stripe "))
		pattern_f = stripe_pattern_create;
	else if (parser_match(parser, " ring "))
		pattern_f = ring_pattern_create;
	if (!pattern_f)
		return (NULL);
	if (parse_color(parser, &color1))
		return ("Invalid pattern color");
	if (!parser_match(parser, " "))
		return ("Invalid pattern format");
	if (parse_color(parser, &color2))
		return ("Invalid pattern color");
	*pattern = pattern_f(color1, color2);
	if (!*pattern)
		return ("Pattern: malloc error");
	return (NULL);
}