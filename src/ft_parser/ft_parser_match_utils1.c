/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_match_utils1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 05:22:17 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/23 07:44:07 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "ft_parser_internal.h"

#include <stdarg.h>
#include <stdbool.h>

bool	parser_match_handle_percent(t_parser *parser, char **fmt_ptr)
{
	if (!parser_match_char(parser, '%'))
		return (false);
	*fmt_ptr = (*fmt_ptr) + 1;
	return (true);
}

bool	parser_match_handle_int(t_parser *parser, char **fmt_ptr, va_list args)
{
	int	i;
	int	*setter;

	if (!parser_consume_int(parser, &i))
		return (false);
	setter = va_arg(args, int *);
	*setter = i;
	*fmt_ptr = (*fmt_ptr) + 1;
	return (true);
}

bool	parser_match_handle_double(t_parser *parser, char **fmt_ptr,
	va_list args)
{
	double	i;
	double	*setter;

	if (!parser_consume_double(parser, &i))
		return (false);
	setter = va_arg(args, double *);
	*setter = i;
	*fmt_ptr = (*fmt_ptr) + 1;
	return (true);
}

bool	parser_match_handle_mandatory_space(t_parser *parser, char **fmt_ptr)
{
	char	*fmt;

	fmt = *fmt_ptr;
	fmt++;
	if (!parser_skip_spaces(parser))
		return (false);
	while (*fmt == ' ' || *fmt == '\t')
		fmt++;
	*fmt_ptr = fmt;
	return (true);
}

bool	parser_match_handle_optional_space(t_parser *parser, char **fmt_ptr)
{
	parser_skip_spaces(parser);
	*fmt_ptr = (*fmt_ptr) + 1;
	return (true);
}
