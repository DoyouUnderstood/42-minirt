/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 05:22:17 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/23 06:27:34 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

#include <stdarg.h>
#include <stdbool.h>

bool	handle_percent(t_parser *parser, char **fmt_ptr)
{
	if (!parser_match_char(parser, '%'))
		return (false);
	*fmt_ptr = (*fmt_ptr) + 1;
	return (true);
}

bool	handle_int(t_parser *parser, char **fmt_ptr, va_list args)
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

bool	handle_double(t_parser *parser, char **fmt_ptr, va_list args)
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

bool	handle_optional_space(t_parser *parser, char **fmt_ptr)
{
	parser_skip_spaces(parser);
	*fmt_ptr = (*fmt_ptr) + 1;
	return (true);
}

bool	handle_end(t_parser *parser, char **fmt_ptr)
{
	if (!parser_at_end(parser))
		return (false);
	*fmt_ptr = (*fmt_ptr) + 1;
	return (true);
}

bool	handle_special(t_parser *parser, char **fmt_ptr, va_list args)
{
	*fmt_ptr = (*fmt_ptr) + 1;
	if (!**fmt_ptr)
		return (false);
	if (**fmt_ptr == '%')
		return (handle_percent(parser, fmt_ptr));
	if (**fmt_ptr == 'd')
		return (handle_int(parser, fmt_ptr, args));
	if (**fmt_ptr == 'f')
		return (handle_double(parser, fmt_ptr, args));
	if (**fmt_ptr == '_')
		return (handle_optional_space(parser, fmt_ptr));
	if (**fmt_ptr == '$')
		return (handle_end(parser, fmt_ptr));
	return (false);
}

bool	handle_mandatory_space(t_parser *parser, char **fmt_ptr)
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

bool	parser_match(t_parser *parser, char *fmt, ...)
{
	va_list	args;
	bool	result;

	va_start(args, fmt);
	result = true;
	while (result && *fmt)
	{
		if (*fmt == '%')
			result = handle_special(parser, &fmt, args);
		else if (*fmt == ' ')
			result = handle_mandatory_space(parser, &fmt);
		else if (!parser_match_char(parser, *fmt++))
			return (false);
	}
	va_end(args);
	return (result);
}