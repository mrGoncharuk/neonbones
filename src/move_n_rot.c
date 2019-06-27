/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_n_rot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 13:52:04 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/27 20:58:46 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "neon.h"

void	ft_turn_right(t_game *game)
{
	double old_dir;
	double old_plane;

	old_dir = game->player.dir.x;
	game->player.dir.x = game->player.dir.x * cos(-(game->player.rot_speed)) -
		game->player.dir.y * sin(-(game->player.rot_speed));
	game->player.dir.y = old_dir * sin(-(game->player.rot_speed)) +
		game->player.dir.y * cos(-(game->player.rot_speed));
	old_plane = game->plane.x;
	game->plane.x = game->plane.x * cos(-(game->player.rot_speed)) -
		game->plane.y * sin(-(game->player.rot_speed));
	game->plane.y = old_plane * sin(-(game->player.rot_speed)) +
		game->plane.y * cos(-(game->player.rot_speed));
	if (game->skybox_ori >= game->ceiling->w - SCR_WIDTH - 5)
		game->skybox_ori = 5;
	else
		game->skybox_ori += 5;
}

void	ft_turn_left(t_game *game)
{
	double old_dir;
	double old_plane;

	old_dir = game->player.dir.x;
	game->player.dir.x = game->player.dir.x * cos(game->player.rot_speed) -
		game->player.dir.y * sin(game->player.rot_speed);
	game->player.dir.y = old_dir * sin(game->player.rot_speed) +
		game->player.dir.y * cos(game->player.rot_speed);
	old_plane = game->plane.x;
	game->plane.x = game->plane.x * cos(game->player.rot_speed) -
		game->plane.y * sin(game->player.rot_speed);
	game->plane.y = old_plane * sin(game->player.rot_speed) +
		game->plane.y * cos(game->player.rot_speed);
	if (game->skybox_ori <= 5)
		game->skybox_ori = game->ceiling->w - SCR_WIDTH - 5;
	else
		game->skybox_ori -= 5;
}
