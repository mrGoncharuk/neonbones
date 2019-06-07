/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caster.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 17:38:26 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/07 20:52:00 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "neon.h"

int		ft_get_step(t_vector2 *h_step, t_vector2 *v_step, double angle)
{
	if (angle >= 0 && angle < 180)
		h_step->y = -WB_SIZE;
	else
		h_step->y = WB_SIZE;
	h_step->x = WB_SIZE / tan(DEG_TO_RAD(angle));

	if (angle >= 90 && angle < 270)
		v_step->x = -WB_SIZE;
	else
		v_step->x = WB_SIZE;
	v_step->y = 64 * tan(DEG_TO_RAD(angle));
}

int		ft_vertical_intersection(t_map *map, t_player *player, double angle)
{
	t_vector2	p;
	t_vector2	step;

	if (angle >= 90 && angle < 270)
		p.x = (int)(player->pos.x / 64) * WB_SIZE - 1;
	else
		p.x = (int)(player->pos.x / 64) * WB_SIZE + 64;
	p.y = player->pos.y + (player->pos.x - p.x) * tan(DEG_TO_RAD(angle));
	while ((map->data[(int)(p.x / WB_SIZE)][(int)(p.y / WB_SIZE)] == 0))
	{
		p.x += step.x;
		p.y += step.y;
	}
}

int		ft_horizontal_intersection(t_game *game, double angle)
{
	t_vector2	p;
	t_vector2	gp;
	t_vector2	step;

	if (angle >= 0 && angle < 180)
		p.y = (int)(game->player.pos.y / 64) * WB_SIZE - 1;
	else
		p.y = (int)(game->player.pos.y / 64) * WB_SIZE + WB_SIZE;
	p.x = game->player.pos.x + (game->player.pos.y - p.y) / tan(DEG_TO_RAD(angle));
	while (game->map.data[(int)(p.x / WB_SIZE)][(int)(p.y / WB_SIZE)] == 0)
	{
		p.x += step.x;
		p.y += step.y;
	}
	return (ft_count_distance());
}

int		ft_wall_finder(t_game *game)
{
	double	angle;
	int		x;

	angle = game->player.camera - game->raycaster.fov / 2;
	x = -1;
	while (++x < SCR_WIDTH)
	{
		// Cast ray to find out distance to the wall
		// Save distance to the wall
		angle += game->raycaster.fov / SCR_WIDTH;
	}
	return (0);
}