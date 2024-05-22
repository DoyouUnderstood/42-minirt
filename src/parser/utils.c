/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:40:05 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/22 12:16:33 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"
#include "parser.h"
#include "get_next_line.h"
#include "ft_printf.h"
#include "libft.h"

#include <fcntl.h>

bool	parse_rgb(char **str, int *value);

// verifie et remplie les tuples.
int	parse_vec3(char *str, t_tuple *vec)
{
	int		count;
	char	*next;

	count = 0;
	vec->x = ft_strtod(str);
	next = advance_to_next_component(&str);
	if (!next)
		return (0);
	count++;
	vec->y = ft_strtod(str);
	next = advance_to_next_component(&str);
	if (!next)
		return (0);
	count++;
	vec->z = ft_strtod(str);
	count++;
	vec->w = 0;
	return (count == 3);
}

// verifie et remplie les R G B
void	rgb(char *str, t_color *color)
{
	int	r;
	int	g;
	int	b;

	if (!parse_rgb(&str, &r) || !in_range(0, 255, r))
		error_exit("error with rgb");
	if (!parse_rgb(&str, &g) || !in_range(0, 255, g))
		error_exit("error with rgb");
	if (!parse_rgb(&str, &b) || !in_range(0, 255, b))
		error_exit("error with rgb");
	if (*str != '\0')
		error_exit("error with rgb");
	color->r = r;
	color->g = g;
	color->b = b;
}


void	free_split(char **parts)
{
	int	i;

	i = 0;
	if (parts)
	{
		while (parts[i])
		{
			free(parts[i]);
			i++;
		}
		free(parts);
	}
}
