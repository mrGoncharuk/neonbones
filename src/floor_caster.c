/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_caster.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 19:37:05 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/23 20:25:49 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "neon.h"

void	ft_set_wall_dir(t_floorcaster *fc, t_raycaster *rc, t_texturer *tex)
{
	if (rc->side == 0 && rc->ray_dir.x > 0)
	{
		fc->floor_wallx = rc->map_coord.x;
		fc->floor_wally = rc->map_coord.y + tex->wall_hit;
	}
	else if (rc->side == 0 && rc->ray_dir.x < 0)
	{
		fc->floor_wallx = rc->map_coord.x + 1.0;
		fc->floor_wally = rc->map_coord.y + tex->wall_hit;
	}
	else if (rc->side == 1 && rc->ray_dir.y > 0)
	{
		fc->floor_wallx = rc->map_coord.x + tex->wall_hit;
		fc->floor_wally = rc->map_coord.y;
	}
	else
	{
		fc->floor_wallx = rc->map_coord.x + tex->wall_hit;
		fc->floor_wally = rc->map_coord.y + 1.0;
	}
}

void	ft_floor_caster(t_game *game, t_raycaster *rc, t_texturer *tex, t_floorcaster *fc, int x)
{
	Uint32	color;
	int		y;
	double	weight;
	
	ft_set_wall_dir(fc, rc, tex);
	fc->wall_dist = rc->wall_dist;
	fc->player_dist = 0;
	if (tex->draw_end < 0)
		tex->draw_end = SCR_HEIGHT;
	y = tex->draw_end;
	while (++y < SCR_HEIGHT)
	{
		fc->curr_dist = SCR_HEIGHT / (2.0 * y - SCR_HEIGHT);
		weight = (fc->curr_dist - fc->player_dist) / (fc->wall_dist - fc->player_dist);
		fc->curr_floorx = weight * fc->floor_wallx + (1 - weight) * game->player.pos.x;
		fc->curr_floory = weight * fc->floor_wally + (1 - weight) * game->player.pos.y;
		fc->floor_texx = (int)(fc->curr_floorx * TEXWIDTH) % TEXWIDTH;
		fc->floor_texy = (int)(fc->curr_floory * TEXHEIGHT) % TEXHEIGHT;
		color = ft_get_pixel32(game->surfaces[4], fc->floor_texx, fc->floor_texy);
		ft_put_pixel32(game->scr_surf, x, y, color);
		//ft_put_pixel32(game->scr_surf, x, SCR_HEIGHT - y, color);
	}
}
