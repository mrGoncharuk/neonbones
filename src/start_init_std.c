/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_init_std.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 17:38:20 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/27 20:48:53 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "neon.h"

void	ft_std_init(t_game *game)
{
	game->fps.currentfps = 0;
	game->fps.deltaclock = 0;
	game->fps.startclock = 0;
	game->plane.x = 0;
	game->plane.y = 0.66;
	game->player.dir.x = -1;
	game->player.dir.y = 0;
	game->player.move_speed = 0.05;
	game->player.rot_speed = 0.03;
	game->player.pos.x -= 0.5;
	game->player.pos.y -= 0.5;
	game->skybox_ori = (game->ceiling->w - SCR_WIDTH) / 2;
	game->texture_compasing = 0;
	game->st_wheel_pos = 1;
	game->moto.speed = 0;
	game->moto.power = 0.005;
	game->moto.friction = 0.97;
	game->moto.forward = 0;
	game->moto.backward = 0;
	game->moto.left = 0;
	game->moto.right = 0;
	SDL_QueryTexture(game->steering[0], NULL, NULL, &(game->st_wheel_w),
					&(game->st_wheel_h));
}
