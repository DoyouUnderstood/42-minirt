/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:40:07 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/21 14:15:44 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "parser.h"
#include "shape_old.h"
#include "get_next_line.h"
#include "ft_printf.h"
#include "libft.h"

#include <fcntl.h>
#include <math.h>

double	ft_pow(double base, int exp)
{
	double	result;

	result = 1;
	while (exp)
	{
		if (exp & 1)
			result *= base;
		exp >>= 1;
		base *= base;
	}
	return (result);
}

int	validate_orientation(const t_tuple *orientation)
{
	double	len;

	len = sqrt(orientation->x * orientation->x + orientation->y * orientation->y
			+ orientation->z * orientation->z);
	if (fabs(len - 1.0) > 1e-6)
		return (0);
	return (1);
}

double	parse_fov(char *str)
{
	double	fov;

	if (!ft_atod((const char *)&str, &fov) || fov <= 0.0 || fov > 180.0)
		return (-1.0);
	return (fov);
}

bool	valid_bright(double bright)
{
	if (bright >= 0 && bright <= 1)
		return (true);
	return (false);
}

char	*advance_to_next_component(char **str)
{
	while (**str && **str != ',')
		(*str)++;
	if (**str == ',')
	{
		(*str)++;
		return (*str);
	}
	else
		return (NULL);
}
