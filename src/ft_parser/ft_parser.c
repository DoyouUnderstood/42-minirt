/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:22:19 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/22 11:05:44 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

void	parser_init(t_parser *parser, char *s)
{
	parser->s = s;
	parser->pos = 0;
}

char	parser_peek(t_parser *parser)
{
	return (parser->s[parser->pos]);
}

char	parser_peek_at(t_parser *parser, int i)
{
	return (parser->s[parser->pos + i]);
}

void	parser_advance(t_parser *parser)
{
	if (parser->s[parser->pos])
		parser->pos++;
}

void	parser_advance_by(t_parser *parser, int i)
{
	parser->pos += i;
}

bool	parser_match_char(t_parser *parser, char c)
{
	if (parser_peek(parser) != c)
		return (false);
	parser_advance(parser);
	return (true);
}

bool	parser_match_alpha(t_parser *parser, char *s)
{
	int	i;

	i = 0;
	while (1)
	{
		if (!s[i])
		{
			parser_advance_by(parser, i);
			return (true);
		}
		if (parser_peek_at(parser, i) != s[i])
			return (false);
		i++;
	}
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

void	parser_skip_spaces(t_parser *parser)
{
	while (parser_match_char(parser, ' ' || parser_match_char(parser, '\t')))
		;
}
