/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 20:04:16 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/27 21:17:24 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "neon.h"

int			ft_get_rand_tile(void)
{
	int		n;

	n = rand() % 20;
	if (n >= 6 && n <= 12)
		return (n);
	else
		return (1);
}

void		ft_load_tiles(t_game *game)
{
	game->surfaces[0] = IMG_Load("res/brick_wall.png");
	game->surfaces[1] = IMG_Load("res/dirty_stone_wall.png");
	game->surfaces[2] = IMG_Load("res/wooden_wall.png");
	game->surfaces[3] = IMG_Load("res/stone_wall.png");
	game->surfaces[4] = IMG_Load("res/floor_road.png");
	game->surfaces[5] = IMG_Load("res/alien_wall.png");
	game->surfaces[6] = IMG_Load("res/grove_wall.png");
	game->surfaces[7] = IMG_Load("res/funny_skeleton_wall.png");
	game->surfaces[8] = IMG_Load("res/skull_wall.png");
	game->surfaces[9] = IMG_Load("res/krishna_wall.png");
	game->surfaces[10] = IMG_Load("res/skull2_wall.png");
	game->surfaces[11] = IMG_Load("res/cleo.png");
	game->surfaces[12] = IMG_Load("res/anime.png");
	game->surfaces[13] = IMG_Load("res/graf_wp1.png");
	game->surfaces[14] = IMG_Load("res/graf_wp2.png");
	game->surfaces[15] = IMG_Load("res/cat.png");
}
