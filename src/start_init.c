/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:31:26 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/23 18:39:11 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "neon.h"
#include <stdio.h>

void	ft_load_textures(t_game *game)
{
	game->scr_surf = SDL_CreateRGBSurface(0, SCR_WIDTH, SCR_HEIGHT, 32,
		0x000000ff, 0x0000ff00, 0x00ff0000, 0);
	game->surfaces[0] = IMG_Load("res/eagle.png");
	game->surfaces[1] = IMG_Load("res/bluestone.png");
	game->surfaces[2] = IMG_Load("res/greystone.png");
	game->surfaces[3] = IMG_Load("res/mossy.png");
	game->surfaces[4] = IMG_Load("res/wood.png");
	game->surfaces[5] = IMG_Load("res/redbrick.png");
	game->surfaces[6] = IMG_Load("res/purplestone.png");
	game->surfaces[7] = IMG_Load("res/colorstone.png");
	// for (int i = 0; i < TEX_NUM; i++)
	// 	if (game->surfaces[i] == NULL)
	// 		printf("Error while loading texture #[%d]\n", i);
}

void	ft_s_sdl_init(t_game *game)
{
	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		ft_putstr("SDL Intialized succesfully\n");
		game->win = SDL_CreateWindow("NeonBone$$$", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_OPENGL);
		if (game->win)
			ft_putstr("Window created!\n");
		game->renderer = SDL_CreateRenderer(game->win, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (game->renderer)
		{
			ft_putstr("Renderer created!\n");
		}
		game->running = 1;
	}
	else
		game->running = 0;
}

void	ft_game_init(t_game *game)
{
	ft_s_sdl_init(game);
	ft_load_textures(game);
	game->player.dir.x = -1;
	game->player.dir.y = 0;
	game->plane.x = 0;
	game->plane.y = 0.66;
	game->timer.currtime = 0;
	game->timer.oldtime = 0;
	game->player.move_speed = 0.05;
	game->player.rot_speed = 0.03;
}
