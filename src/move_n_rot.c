/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_n_rot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 13:52:04 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/23 18:40:00 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "neon.h"

void	ft_move_forward(t_game *game)
{
	if (game->map.data[(int)(game->player.pos.x + game->player.dir.x *
		game->player.move_speed)][(int)(game->player.pos.y)] == 0)
		game->player.pos.x += game->player.dir.x * game->player.move_speed;
	if (game->map.data[(int)(game->player.pos.x)][(int)(game->player.pos.y +
		game->player.dir.y * game->player.move_speed)] == 0)
		game->player.pos.y += game->player.dir.y * game->player.move_speed;
}

void	ft_move_backward(t_game *game)
{
	if (game->map.data[(int)(game->player.pos.x - game->player.dir.x *
		game->player.move_speed)][(int)(game->player.pos.y)] == 0)
		game->player.pos.x -= game->player.dir.x * game->player.move_speed;
	if (game->map.data[(int)(game->player.pos.x)][(int)(game->player.pos.y -
		game->player.dir.y * game->player.move_speed)] == 0)
		game->player.pos.y -= game->player.dir.y * game->player.move_speed;
}

void	ft_turn_right(t_game *game)
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
}

void	ft_turn_left(t_game *game)
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
}
