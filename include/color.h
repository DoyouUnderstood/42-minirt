/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:26:50 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/23 13:58:46 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <stdbool.h>

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}			t_color;

typedef struct s_color_255
{
	int	r;
	int	g;
	int	b;
}	t_color_255;

t_color	color_create(double r, double g, double b);
bool	color_eq(t_color c1, t_color c2);
t_color	color_add(t_color c1, t_color c2);
t_color	color_multiply(t_color c1, t_color c2);
t_color	color_multiply_scalar(t_color c, double scalar);
int		color_to_int(t_color color);
t_color	color_from_255(t_color_255 color_255);
bool	color_255_validate(t_color_255 color_255);

#endif