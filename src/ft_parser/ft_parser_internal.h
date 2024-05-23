/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 06:57:23 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/23 07:09:43 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSER_INTERNAL_H
# define FT_PARSER_INTERNAL_H

# include "ft_parser.h"

# include <stdbool.h>

// Parser utils
char	parser_peek(t_parser *parser);
char	parser_peek_at(t_parser *parser, int i);
void	parser_advance(t_parser *parser);
void	parser_advance_by(t_parser *parser, int i);
bool	parser_match_char(t_parser *parser, char c);
bool	parser_consume_int(t_parser *parser, int *i);
bool	parser_consume_double(t_parser *parser, double *d);
bool	parser_skip_spaces(t_parser *parser);
bool	parser_at_end(t_parser *parser);

// Parser match utils
bool	parser_match_handle_percent(t_parser *parser, char **fmt_ptr);
bool	parser_match_handle_int(t_parser *parser, char **fmt_ptr,
			va_list args);
bool	parser_match_handle_double(t_parser *parser, char **fmt_ptr,
			va_list args);
bool	parser_match_handle_optional_space(t_parser *parser, char **fmt_ptr);
bool	parser_match_handle_end(t_parser *parser, char **fmt_ptr);
bool	parser_match_handle_special(t_parser *parser, char **fmt_ptr,
			va_list args);
bool	parser_match_handle_mandatory_space(t_parser *parser, char **fmt_ptr);



#endif