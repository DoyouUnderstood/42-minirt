/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:22:19 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/23 07:43:11 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "ft_parser_internal.h"

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

bool	parser_match_char(t_parser *parser, char c)
{
	if (parser_peek(parser) != c)
		return (false);
	parser_advance(parser);
	return (true);
}

bool	parser_consume_int(t_parser *parser, int *i)
{
	int		sign;
	char	c;

	*i = 0;
	sign = 1;
	if (parser_match_char(parser, '-'))
		sign = -1;
	else if (parser_match_char(parser, '+'))
	{}
	c = parser_peek(parser);
	if (c < '0' || c > '9')
		return (false);
	while (c >= '0' && c <= '9')
	{
		*i = *i * 10 + (c - '0');
		parser_advance(parser);
		c = parser_peek(parser);
	}
	*i = *i * sign;
	return (true);
}

bool	parser_consume_double(t_parser *parser, double *d)
{
	double	sign;
	char	c;
	double	power;

	*d = 0.0;
	sign = 1.0;
	if (parser_match_char(parser, '-'))
		sign = -1.0;
	else if (parser_match_char(parser, '+'))
	{}
	c = parser_peek(parser);
	if (c < '0' || c > '9')
		return (false);
	while (c >= '0' && c <= '9')
	{
		*d = *d * 10 + (c - '0');
		parser_advance(parser);
		c = parser_peek(parser);
	}
	if (!parser_match_char(parser, '.'))
	{
		*d = *d * sign;
		return (true);
	}
	power = -1.0;
	c = parser_peek(parser);
	while (c >= '0' && c <= '9')
	{
		*d = *d + (c - '0') * pow(10, power--);
		parser_advance(parser);
		c = parser_peek(parser);
	}
	*d = *d * sign;
	return (true);
}

bool	parser_skip_spaces(t_parser *parser)
{
	if (!parser_match_char(parser, ' ') && !parser_match_char(parser, '\t'))
		return (false);
	while (parser_match_char(parser, ' ') || parser_match_char(parser, '\t'))
	{}
	return (true);
}

bool	parser_at_end(t_parser *parser)
{
	return (parser_peek(parser) == '\0');
}