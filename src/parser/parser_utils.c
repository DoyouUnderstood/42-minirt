/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:41:43 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 04:43:01 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "parser.h"

char	*parse_reflectivity(t_parser *parser, double *reflectivity)
{
	if (!parser_match(parser, " %f", reflectivity))
		*reflectivity = 0.0;
	return (NULL);
}

char	*parse_pattern(t_parser *parser, t_pattern **pattern)
{
	t_parser_pattern	d;

	d.pattern_f = NULL;
	*pattern = NULL;
	if (parser_match(parser, " gradient "))
		d.pattern_f = gradient_pattern_create;
	else if (parser_match(parser, " checker "))
		d.pattern_f = checker_pattern_create;
	else if (parser_match(parser, " stripe "))
		d.pattern_f = stripe_pattern_create;
	else if (parser_match(parser, " ring "))
		d.pattern_f = ring_pattern_create;
	if (!d.pattern_f)
		return (NULL);
	if (!parser_match(parser, "%d,%d,%d %d,%d,%d",
		&d.color1.r, &d.color1.g, &d.color1.b,
		&d.color2.r, &d.color2.g, &d.color2.b))
		return ("Invalid pattern format");
	if (!color_255_validate(d.color1) || !color_255_validate(d.color2))
		return ("Invalid pattern color");
	*pattern = d.pattern_f(color_from_255(d.color1), color_from_255(d.color2));
	if (!*pattern)
		return ("Pattern: malloc error");
	return (NULL);
}