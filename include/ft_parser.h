/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:20:54 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/22 11:04:52 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSER_H
# define FT_PARSER_H

# include <stdbool.h>

typedef struct s_parser
{
	char	*s;
	int		pos;
}	t_parser;

void	parser_init(t_parser *parser, char *s);
bool	parser_match_char(t_parser *parser, char c);
bool	parser_match_alpha(t_parser *parser, char *s);
bool	parser_consume_int(t_parser *parser, int *i);
bool	parser_consume_double(t_parser *parser, double *d);

#endif