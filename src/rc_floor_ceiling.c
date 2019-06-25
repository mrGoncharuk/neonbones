/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_floor_ceiling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 19:01:30 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/25 18:15:02 by mhonchar         ###   ########.fr       */
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

void	ft_draw_ceiling(t_game *game, t_texturer *tex, t_floorcaster *fc, int x)
{
	int		y;
	double	w;
	Uint32	color;

	y = tex->draw_end;
	while (++y < SCR_HEIGHT)
	{
		fc->curr_dist = SCR_HEIGHT / (2.0 * y - SCR_HEIGHT);
		w = (fc->curr_dist - fc->player_dist) /
			(fc->wall_dist - fc->player_dist);
		fc->curr_floorx = w * fc->floor_wallx + (1 - w) * game->player.pos.x;
		fc->curr_floory = w * fc->floor_wally + (1 - w) * game->player.pos.y;
		fc->floor_texx = (int)(fc->curr_floorx * game->ceiling->w / 20) %
						game->ceiling->w;
		fc->floor_texy = (int)(fc->curr_floory * game->ceiling->h / 11) %
						game->ceiling->h;
		color = ft_get_pixel32(game->ceiling, fc->floor_texx, fc->floor_texy);
		ft_put_pixel32(game->scr_surf, x, SCR_HEIGHT - y, color);
	}
}

void	ft_draw_floor(t_game *game, t_texturer *tex, t_floorcaster *fc, int x)
{
	int		y;
	double	w;
	Uint32	color;

	y = tex->draw_end;
	while (++y < SCR_HEIGHT)
	{
		fc->curr_dist = SCR_HEIGHT / (2.0 * y - SCR_HEIGHT);
		w = (fc->curr_dist - fc->player_dist) /
			(fc->wall_dist - fc->player_dist);
		fc->curr_floorx = w * fc->floor_wallx + (1 - w) * game->player.pos.x;
		fc->curr_floory = w * fc->floor_wally + (1 - w) * game->player.pos.y;
		fc->floor_texx = (int)(fc->curr_floorx * TEXWIDTH) % TEXWIDTH;
		fc->floor_texy = (int)(fc->curr_floory * TEXHEIGHT) % TEXHEIGHT;
		color = ft_get_pixel32(game->surfaces[4], fc->floor_texx,
				fc->floor_texy);
		ft_put_pixel32(game->scr_surf, x, y, color);
	}
}

void	ft_floor_caster(t_game *game, t_raycaster *rc, t_texturer *tex,
							t_floorcaster *fc)
{
	int		x;

	x = fc->x;
	ft_set_wall_dir(fc, rc, tex);
	fc->wall_dist = rc->wall_dist;
	fc->player_dist = 0;
	if (tex->draw_end < 0)
		tex->draw_end = SCR_HEIGHT;
	ft_draw_floor(game, tex, fc, x);
}

void	ft_create_skybox(t_game *game)
{
	SDL_Rect ceiling_rect;
	SDL_Rect scr_rect;

	scr_rect.x = 0;
	scr_rect.y = 0;
	ceiling_rect.x = 0 + game->skybox_ori;
	ceiling_rect.y = 0;
	ceiling_rect.w = SCR_WIDTH + game->skybox_ori;
	ceiling_rect.h = SCR_HEIGHT / 2;
	SDL_BlitSurface(game->ceiling, &ceiling_rect, game->scr_surf, &scr_rect);
}
