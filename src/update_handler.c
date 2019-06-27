/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:55:37 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/27 19:59:19 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "neon.h"

float	ft_coll_fac(float moto_speed)
{
	if (moto_speed < 0 && moto_speed > -0.08)
		return (-0.08f);
	if (moto_speed > 0 && moto_speed < 0.08)
		return (0.08f);
	return (moto_speed);
}

void	ft_accelerate(t_game *game)
{
	if (game->moto.forward && !(game->moto.backward))
		if (game->moto.speed < 0.3)
			game->moto.speed += game->moto.power;
	if (!game->moto.forward && (game->moto.backward))
		if (game->moto.speed > -0.1)
			game->moto.speed -= game->moto.power;
	if (game->map.data[(int)(game->player.pos.y)][(int)(game->player.pos.x +
		2 * game->player.dir.x * ft_coll_fac(game->moto.speed))] == 0)
		game->player.pos.x += game->player.dir.x * game->moto.speed;
	else
		game->moto.speed = 0;
	if (game->map.data[(int)(game->player.pos.y + 2 * game->player.dir.y *
		ft_coll_fac(game->moto.speed))][(int)(game->player.pos.x)] == 0)
		game->player.pos.y += game->player.dir.y * game->moto.speed;
	else
		game->moto.speed = 0;
	game->moto.speed *= game->moto.friction;
	if (ft_abs(game->moto.speed) <= 0.0001)
		game->moto.speed = 0;
}

void	ft_update(t_game *game)
{
	ft_accelerate(game);
	if ((game->moto.left && !game->moto.right && (game->moto.speed > 0)) ||
		(game->moto.right && (game->moto.speed < 0)))
		ft_turn_left(game);
	if ((!game->moto.left && game->moto.right && (game->moto.speed > 0)) ||
		(game->moto.left && (game->moto.speed < 0)))
		ft_turn_right(game);
	ft_create_skybox(game);
	caster(game);
}
