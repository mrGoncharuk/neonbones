/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:31:26 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/27 20:52:57 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "neon.h"

int		ft_load_steer_textures(t_game *game)
{
	if (sdl_texture_manager(game->renderer, &(game->steering[0]),
							"res/steer_left.png") < 0)
		return (-1);
	if (sdl_texture_manager(game->renderer, &(game->steering[1]),
							"res/steering_bar.png") < 0)
		return (-1);
	if (sdl_texture_manager(game->renderer, &(game->steering[2]),
							"res/steer_right.png") < 0)
		return (-1);
	return (0);
}

int		ft_load_textures(t_game *game)
{
	int		i;

	game->scr_surf = SDL_CreateRGBSurface(0, SCR_WIDTH, SCR_HEIGHT, 32,
		0x000000ff, 0x0000ff00, 0x00ff0000, 0);
	ft_load_tiles(game);
	game->ceiling = IMG_Load("res/fin_skybox.png");
	i = -1;
	while (++i < TEX_NUM)
		if (game->surfaces[i] == NULL)
			return (-1);
	if (!game->scr_surf || !game->ceiling)
		return (-1);
	if (ft_load_steer_textures(game) < 0)
		return (-1);
	return (0);
}

int		ft_s_sdl_init(t_game *game)
{
	int		success;

	success = 1;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0)
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

int		ft_load_music(t_game *game)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
		return (-1);
	game->background_sound = Mix_LoadMUS("res/Death_Grips_Hustle_Bones.ogg");
	if (game->background_sound == NULL)
		return (-1);
	return (0);
}

int		ft_game_init(t_game *game)
{
	if (ft_s_sdl_init(game) < 0)
		return (-1);
	if (ft_load_textures(game) < 0)
		return (-1);
	if (ft_load_music(game) < 0)
		return (-1);
	ft_std_init(game);
	return (0);
}
