/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computation.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:26:50 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/21 11:27:27 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTATION_H
# define COMPUTATION_H

# include "color.h"
# include "object.h"
# include "tuple.h"

typedef struct s_computations
{
	double					t;
	t_object				*object;
	t_tuple					point;
	t_tuple					over_point;
	t_tuple					eyev;
	t_tuple					normalv;
	t_tuple					reflectv;
	t_color					*color;
	bool					inside;
}							t_computations;


#endif