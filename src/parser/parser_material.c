/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_material.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:41:43 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 05:45:39 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"
#include "ft_parser.h"

#include <stdlib.h>

static char	*parse_reflectivity(t_parser *parser, double *reflectivity)
{
	if (!parser_match(parser, " %f", reflectivity))
		*reflectivity = 0.0;
	if (*reflectivity < 0.0 || *reflectivity > 1.0)
		return ("Invalid reflectivity");
	return (NULL);
}

static char	*parse_pattern(t_parser *parser, t_pattern **pattern)
{
	t_pattern	*(*pattern_f)(t_color c1, t_color c2);
	t_color_255	color_255_1;
	t_color_255	color_255_2;

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
	if (!parser_match(parser, "%d,%d,%d %d,%d,%d",
		&color_255_1.r, &color_255_1.g, &color_255_1.b,
		&color_255_2.r, &color_255_2.g, &color_255_2.b))
		return ("Invalid pattern format");
	if (!color_255_validate(color_255_1) || !color_255_validate(color_255_2))
		return ("Invalid pattern color");
	*pattern = pattern_f(color_from_255(color_255_1),
			color_from_255(color_255_2));
	return (NULL);
}

char	*parse_material(t_parser *parser, t_material *material)
{
	char	*error;

	error = parse_reflectivity(parser, &material->reflectiv);
	if (!error)
		error = parse_pattern(parser, &material->pattern);
	return (error);
	
}