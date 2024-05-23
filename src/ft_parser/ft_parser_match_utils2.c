/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_match_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 05:22:17 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/23 07:43:32 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "ft_parser_internal.h"

#include <stdarg.h>
#include <stdbool.h>

bool	parser_match_handle_end(t_parser *parser, char **fmt_ptr)
{
	if (!parser_at_end(parser))
		return (false);
	*fmt_ptr = (*fmt_ptr) + 1;
	return (true);
}

bool	parser_match_handle_special(t_parser *parser, char **fmt_ptr,
	va_list args)
{
	*fmt_ptr = (*fmt_ptr) + 1;
	if (!**fmt_ptr)
		return (false);
	if (**fmt_ptr == '%')
		return (parser_match_handle_percent(parser, fmt_ptr));
	if (**fmt_ptr == 'd')
		return (parser_match_handle_int(parser, fmt_ptr, args));
	if (**fmt_ptr == 'f')
		return (parser_match_handle_double(parser, fmt_ptr, args));
	if (**fmt_ptr == '_')
		return (parser_match_handle_optional_space(parser, fmt_ptr));
	if (**fmt_ptr == '$')
		return (parser_match_handle_end(parser, fmt_ptr));
	return (false);
}
