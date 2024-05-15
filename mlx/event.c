#include "../include/minilibx.h"

# define KEY_ESC 'e'
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
