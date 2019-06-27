/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:30:21 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/27 17:46:04 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "neon.h"

void	ft_keydown_handler(t_game *game, int key)
{
	if (key == SDLK_UP)
		game->moto.forward = 1;
	if (key == SDLK_DOWN)
		game->moto.backward = 1;
	if (key == SDLK_RIGHT)
	{
		game->st_wheel_pos = 2;
		game->moto.right = 1;
	}
	if (key == SDLK_LEFT)
	{
		game->st_wheel_pos = 0;
		game->moto.left = 1;
	}
	if (key == SDLK_q)
		game->texture_compasing = !game->texture_compasing;
	if (key == SDLK_ESCAPE)
		game->running = 0;
}

void	ft_keyup_handler(t_game *game, int key)
{
	if (key == SDLK_UP)
		game->moto.forward = 0;
	if (key == SDLK_DOWN)
		game->moto.backward = 0;
	if (key == SDLK_RIGHT)
		game->moto.right = 0;
	if (key == SDLK_LEFT)
		game->moto.left = 0;
}

void	ft_event_handler(t_game *game)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			game->running = 0;
		if (event.type == SDL_KEYDOWN)
		{
			ft_keydown_handler(game, event.key.keysym.sym);
		}
		if (event.type == SDL_KEYUP)
		{
			ft_keyup_handler(game, event.key.keysym.sym);
			if (event.key.keysym.sym == SDLK_RIGHT ||
				event.key.keysym.sym == SDLK_LEFT)
				game->st_wheel_pos = 1;
		}
	}
}
