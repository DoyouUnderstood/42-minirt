/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:22:19 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/23 07:10:13 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

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
