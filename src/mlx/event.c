/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:37:19 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/21 18:24:28 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx.h"

#include <stdlib.h>

// fonction evenement pour quitter avec echap
int	mlx_event_handle_keypress(int key, t_mlx *mlx)
{
	if (key == 53)
	{
		mlx_cleanup(mlx);
		exit(0);
	}
	return (0);
}

// fonction pour quitter avec la croix rouge
int	mlx_event_close_win(t_mlx *mlx)
{
	mlx_cleanup(mlx);
	exit(0);
	return (0);
}
