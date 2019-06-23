/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caster.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 14:06:53 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/23 18:26:14 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "neon.h"

void	ft_calc_initial(t_raycaster *rc, t_game *game, int x)
{
	rc->cam.x = 2 * x / (double)SCR_WIDTH - 1;
	rc->ray_dir.x = game->player.dir.x + game->plane.x * rc->cam.x;
	rc->ray_dir.y = game->player.dir.y + game->plane.y * rc->cam.x;
	rc->map_coord.x = (int)(game->player.pos.x);
	rc->map_coord.y = (int)(game->player.pos.y);
	rc->delta_dist.x = fabs(1 / rc->ray_dir.x);
	rc->delta_dist.y = fabs(1 / rc->ray_dir.y);
	rc->hit = 0;
}

void	ft_set_steps(t_raycaster *rc, t_player *player)
{
	if (rc->ray_dir.x < 0)
	{
		rc->step.x = -1;
		rc->side_dist.x = (player->pos.x - rc->map_coord.x) * rc->delta_dist.x;
	}
	else
	{
		rc->step.x = 1;
		rc->side_dist.x = (rc->map_coord.x + 1.0f - player->pos.x) *
			rc->delta_dist.x;
	}
	if (rc->ray_dir.y < 0)
	{
		rc->step.y = -1;
		rc->side_dist.y = (player->pos.y - rc->map_coord.y) * rc->delta_dist.y;
	}
	else
	{
		rc->step.y = 1;
		rc->side_dist.y = (rc->map_coord.y + 1.0 - player->pos.y) *
			rc->delta_dist.y;
	}
}

void	ft_calc_dist(t_raycaster *rc, t_game *game)
{
	while (rc->hit == 0)
	{
		if (rc->side_dist.x < rc->side_dist.y)
		{
			rc->side_dist.x += rc->delta_dist.x;
			rc->map_coord.x += rc->step.x;
			rc->side = 0;
		}
		else
		{
			rc->side_dist.y += rc->delta_dist.y;
			rc->map_coord.y += rc->step.y;
			rc->side = 1;
		}
		if (game->map.data[rc->map_coord.x][rc->map_coord.y] > 0)
			rc->hit = 1;
	}
	if (rc->side == 0)
		rc->wall_dist = (rc->map_coord.x - game->player.pos.x +
			(1 - rc->step.x) / 2) / rc->ray_dir.x;
	else
		rc->wall_dist = (rc->map_coord.y - game->player.pos.y +
			(1 - rc->step.y) / 2) / rc->ray_dir.y;
}

void	ft_texturing_calc(t_game *game, t_raycaster *rc, t_texturer *tex)
{
	tex->line_height = (int)(SCR_HEIGHT / rc->wall_dist);
	tex->draw_start = -tex->line_height / 2 + SCR_HEIGHT / 2;
	if (tex->draw_start < 0)
		tex->draw_start = 0;
	tex->draw_end = tex->line_height / 2 + SCR_HEIGHT / 2;
	if (tex->draw_end >= SCR_HEIGHT)
		tex->draw_end = SCR_HEIGHT - 1;
	tex->tex_num = game->map.data[rc->map_coord.x][rc->map_coord.y] - 1;
	if (rc->side == 0)
		tex->wall_hit = game->player.pos.y + rc->wall_dist * rc->ray_dir.y;
	else
		tex->wall_hit = game->player.pos.x + rc->wall_dist * rc->ray_dir.x;
	tex->wall_hit -= (int)(tex->wall_hit);
	tex->tex_hit = (int)(tex->wall_hit * (double)TEXWIDTH);
	if (rc->side == 0 && rc->ray_dir.x > 0)
		tex->tex_hit = TEXWIDTH - tex->tex_hit - 1;
	if (rc->side == 1 && rc->ray_dir.y < 0)
		tex->tex_hit = TEXWIDTH - tex->tex_hit - 1;
}

void	ft_texturing_walls(t_game *game, t_raycaster *rc, t_texturer *tex, int x)
{
	int			y;
	int			d;
	int			tex_y;
	Uint32		color;

	y = tex->draw_start - 1;
	while (++y < tex->draw_end)
	{
		d = y * 256 - SCR_HEIGHT * 128 + tex->line_height * 128;
		tex_y = ((d * TEXHEIGHT) / tex->line_height) / 256;
		color = ft_get_pixel32(game->surfaces[tex->tex_num], tex->tex_hit, tex_y);
		if (rc->side == 1)
			color = (color >> 1) & 8355711;
		ft_put_pixel32(game->scr_surf, x, y, color);
	}
}

void	caster(t_game *game)
{
	t_raycaster	rc;
	t_texturer	tex;
	int			x;

	x = -1;
	while (++x < SCR_WIDTH)
	{
		ft_calc_initial(&rc, game, x);
		ft_set_steps(&rc, &(game->player));
		ft_calc_dist(&rc, game);
		ft_texturing_calc(game, &rc, &tex);
		ft_texturing_walls(game, &rc, &tex, x);
	}
	// time_t seconds;
	// time(&seconds);
	// game->timer.oldtime = game->timer.currtime;
	// game->timer.currtime = seconds;
	// double frame_time = (game->timer.currtime - game->timer.oldtime);
	// printf("FPS: [%f]\n", 1.0 / frame_time);
	// game->player.move_speed = 0.05; //the constant value is in squares/second
	// game->player.rot_speed = 0.03; //the constant value is in radians/second
}
