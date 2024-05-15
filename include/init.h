/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:01:31 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/15 16:01:32 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

typedef struct s_world	t_world;
typedef struct s_camera	t_camera;
typedef struct s_mlx	t_mlx;

void					world_init(t_world **world, t_camera **camera);
void					world_fill(t_world *world);
void					mlx_initialisation(t_world *world);

#endif
