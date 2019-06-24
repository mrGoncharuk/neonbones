/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 18:53:13 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/24 19:20:42 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "neon.h"

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
