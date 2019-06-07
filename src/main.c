/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 16:48:24 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/07 20:19:57 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "neon.h"

int		ft_scene_render(t_game* game)
{
	(void)game;
	return (0);
}

// void	ft_start_initializer(t_game *game)
// {

	

// }

// void	ft_mainloop(t_game *game)
// {
// 	SDL_Event	event;
// 	int			running;

// 	SDL_Init(SDL_INIT_VIDEO);
// 	game->win = SDL_CreateWindow("NeonBone$$$", SDL_WINDOWPOS_CENTERED,
// 		SDL_WINDOWPOS_CENTERED, SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_OPENGL);
// 	game->renderer = SDL_CreateRenderer(game->win, -1,
// 		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
// 	SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
// 	running = 1;
// 	while (running)
// 	{
// 		while (SDL_PollEvent(&event))
// 		{
// 			if (event.type == SDL_QUIT)
// 				running = 0;
// 		}
// 	}
// 	SDL_DestroyRenderer(game->renderer);
// 	SDL_DestroyWindow(game->win);
// 	SDL_Quit();
// }




int		main(int argc, char **argv)
{
	t_game		game;
	int			ret;
	
	if (argc != 2)
	{
		(void)argv;
		write(1, "lol\n", 4);
		return (0);
	}
	if ((ret = ft_read_map(&game, argv[1])) < 0)
	{
		printf ("Error code: %d\n", ret);
		system("leaks NeonBones");
		return (0);
	}
	ft_mainloop(&game);



	return (0);
}