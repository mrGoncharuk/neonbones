/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:31:26 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/24 19:49:57 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "neon.h"
#include <stdio.h>

int		ft_load_textures(t_game *game)
{
	int		i;

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
	game->surfaces[8] = IMG_Load("res/cat.jpg");
	game->ceiling = IMG_Load("res/nebo.png");
	
	i = -1;
	while (++i < TEX_NUM)
		if (game->surfaces[i] == NULL)
			return (-1);
	if (!game->scr_surf || !game->ceiling)
		return (-1);
	ft_putendl("Textures loaded successful.");
	return (0);
}

int		ft_s_sdl_init(t_game *game)
{
	int		success;

	success = 1;
	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		game->win = SDL_CreateWindow("NeonBone$$$", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_OPENGL);
		if (game->win == NULL)
			success = 0;
		game->renderer = SDL_CreateRenderer(game->win, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (game->renderer == NULL)
			success = 0;
		game->running = 1;
		if (TTF_Init() == -1)
			success = 0;
		game->font = TTF_OpenFont("res/OpenSans-Bold.ttf", 15);
		if (game->font == NULL)
			success = 0;
	}
	else
		success = 0;
	if (success == 0)
		return (-1);
	return (0);
}

int		ft_game_init(t_game *game)
{
	if (ft_s_sdl_init(game) < 0)
		return (-1);
	if (ft_load_textures(game) < 0)
		return (-1);
	game->fps.currentfps = 0;
	game->fps.deltaclock = 0;
	game->fps.startclock = 0;
	game->player.dir.x = -1;
	game->player.dir.y = 0;
	game->plane.x = 0;
	game->plane.y = 0.66;
	game->player.move_speed = 0.05;
	game->player.rot_speed = 0.03;
	return (0);
}
