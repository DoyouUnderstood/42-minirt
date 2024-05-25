/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:33:27 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/25 04:54:57 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool	double_eq(double x, double y)
{
	if (x > y)
		return (x - y < TUPLE_EPSILON);
	return (y - x < TUPLE_EPSILON);
}

double	dclamp(double x, double min, double max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

void	error_exit(char *error_msg)
{
	printf("%s\n", error_msg);
	exit(1);
}
