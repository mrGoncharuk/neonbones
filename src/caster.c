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
#include <stdio.h>
/*
**	There is in case that intersection point can be located out of map 
**	distance can gain value -1
**	if statement checks the case of -1 of values and comenti-xyementi
*/
int		ft_choose_dist(int a, int b)
{
	if (b < 0 || ((a < b) && (a >= 0)))
		return (a);
	else
		return (b);
}

int		ft_calc_distance(t_player *player, t_vector2 wall, float angle)
{
	int		distance;

	distance = abs(player->pos.x - wall.x) / cos(DEG_TO_RAD(angle));
	distance = distance / cos((double)(DEG_TO_RAD(player->camera - angle)));
	return (distance);
}

int		ft_is_out_map(int x, int y, int map_width, int map_height)
{
	if (x < 0 || x >= map_width || y < 0 || y >= map_height)
		return (1);
	return (0);
}

t_vector2		ft_get_h_step(float angle)
{
	t_vector2	h_step;

	if (angle >= 0 && angle < 180)
		h_step.y = -WB_SIZE;
	else
		h_step.y = WB_SIZE;
	h_step.x = WB_SIZE / tan(DEG_TO_RAD(angle));
	return (h_step);
}

t_vector2		ft_get_v_step(float angle)
{
	t_vector2 v_step;

	if (angle >= 90 && angle < 270)
		v_step.x = -WB_SIZE;
	else
		v_step.x = WB_SIZE;
	v_step.y = WB_SIZE * tan(DEG_TO_RAD(angle));
	return (v_step);
}

int		ft_vertical_intersection(t_map *map, t_player *player, t_vector2 step, float angle)
{
	t_vector2	p;
	int			x;
	int			y;

	if (angle >= 90 && angle < 270)
		p.x = (int)(player->pos.x / 64) * WB_SIZE - 1;
	else
		p.x = (int)(player->pos.x / 64) * WB_SIZE + 64;
	p.y = player->pos.y + (player->pos.x - p.x) * tan((double)DEG_TO_RAD(angle));
	x = (int)(p.x / WB_SIZE);
	y = (int)(p.y / WB_SIZE);
	if (ft_is_out_map(x, y, map->width, map->height))
		return (-1);
	while ((map->data[y][x] == 0))
	{
		p.x += step.x;
		p.y += step.y;
		x = (int)(p.x / WB_SIZE);
		y = (int)(p.y / WB_SIZE);
		if (ft_is_out_map(x, y, map->width, map->height))
			return (-1);
	}
	return (ft_calc_distance(player, p, angle));
}

int		ft_horizontal_intersection(t_map* map, t_player* player, t_vector2 step, float angle)
{
	t_vector2	p;
	int			x;
	int			y;

	if (angle >= 0 && angle < 180)
		p.y = (int)(player->pos.y / 64) * WB_SIZE - 1;
	else
		p.y = (int)(player->pos.y / 64) * WB_SIZE + WB_SIZE;
	p.x = player->pos.x + (player->pos.y - p.y) / tan(DEG_TO_RAD(angle));
	x = (int)(p.x / WB_SIZE);
	y = (int)(p.y / WB_SIZE);
	if (ft_is_out_map(x, y, map->width, map->height))
		return (-1);
	while ((map->data[y][x] == 0))
	{
		p.x += step.x;
		p.y += step.y;
		x = (int)(p.x / WB_SIZE);
		y = (int)(p.y / WB_SIZE);
		if (ft_is_out_map(x, y, map->width, map->height))
			return (-1);
	}
	return (ft_calc_distance(player, p, angle));
}

int		ft_wall_finder(t_game *game)
{
	float		angle;
	int			x;
	t_vector2	v_step;
	t_vector2	h_step;
	int			hor;
	int			ver;

	angle = game->player.camera - game->raycaster.fov / 2;
	x = -1;
	printf("angle [%f] inc [%f]\n", angle, (double)(game->raycaster.fov / SCR_WIDTH));
	printf("p.x = [ %d ]   p.y =[ %d ]\n", game->player.pos.x, game->player.pos.y);
	while (++x < SCR_WIDTH)
	{
		// Cast ray to find out distance to the wall
		// Save distance to the wall
		hor = ft_horizontal_intersection(&(game->map), &(game->player), ft_get_h_step(angle), angle);
		ver = ft_vertical_intersection(&(game->map), &(game->player), ft_get_v_step(angle), angle);
	
		//printf("angle [%f]\n", angle);
		angle += game->raycaster.fov / SCR_WIDTH;
		
		printf("dist = %d\n", ft_choose_dist(hor, ver));

		//if (MIN(hor, ver) == -1)
		//	printf("dist[ %d ]\n", MAX(hor, ver));
		//else
		//	printf("dist[ %d ]\n", MIN(hor, ver));
		//printf("horizontal [ %d ]   vertical[ %d ]\n", hor, ver);
	}
	return (0);
}