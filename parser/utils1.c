/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:32:26 by ltd               #+#    #+#             */
/*   Updated: 2024/05/15 20:33:27 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics/graphics.h"
#include "../include/init.h"
#include "../include/parser.h"
#include "../include/shape.h"
#include "../lib/GNL/get_next_line.h"
#include "../lib/ft_printf/ft_printf.h"
#include "../lib/libft/libft.h"
#include <fcntl.h>

// check if its in range rover
bool	in_range(double start, double end, double value)
{
	return (value >= start && value <= end);
}

double	validate_reflectivity(double value)
{
	if (value < 0.0 || value > 1.0)
		error_exit("Invalid reflectivity value");
	return (value);
}

int	ft_atoi_rgb(char **str)
{
	int	res;

	res = 0;
	while (**str >= '0' && **str <= '9')
	{
		res = res * 10 + (**str - '0');
		(*str)++;
	}
	return (res);
}

bool	parse_rgb(char **str, int *value)
{
	if (**str == '\0' || (**str == ',' && *(*str + 1) == '\0'))
		return (false);
	*value = ft_atoi_rgb(str);
	if (**str == ',')
		(*str)++;
	return (true);
}
