/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:37:19 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/15 17:37:33 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minilibx.h"

// fonction evenement pour quitter avec echap
int	mlx_event_handle_keypress(int keysym, t_mlx *mlx)
{
	if (keysym == KEY_ESC)
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
