/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 18:53:13 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/25 19:28:17 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "neon.h"

void	ft_select_texture(t_raycaster *rc, t_texturer *tex)
{
	if (rc->side == 0 && rc->ray_dir.x > 0)
		tex->tex_num = 1;
	if (rc->side == 0 && rc->ray_dir.x < 0)
		tex->tex_num = 2;
	if (rc->side == 1 && rc->ray_dir.y > 0)
		tex->tex_num = 3;
	if (rc->side == 1 && rc->ray_dir.y < 0)
		tex->tex_num = 4;
}

void	caster(t_game *game)
{
	t_raycaster		rc;
	t_texturer		tex;
	t_floorcaster	fc;
	int				x;

	x = -1;
	while (++x < SCR_WIDTH)
	{
		ft_calc_initial(&rc, game, x);
		ft_set_steps(&rc, &(game->player));
		ft_calc_dist(&rc, game);
		ft_texturing_calc(game, &rc, &tex);
		ft_texturing_walls(game, &rc, &tex, x);
		fc.x = x;
		ft_floor_caster(game, &rc, &tex, &fc);
	}
}
