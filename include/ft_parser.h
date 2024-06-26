/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:20:54 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/23 06:58:25 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSER_H
# define FT_PARSER_H

# include <stdarg.h>
# include <stdbool.h>

typedef struct s_parser
{
	char	*s;
	int		pos;
}	t_parser;

void	parser_init(t_parser *parser, char *s);
bool	parser_match(t_parser *parser, char *fmt, ...);

#endif