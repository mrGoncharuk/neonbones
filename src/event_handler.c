/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:30:21 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/26 21:52:15 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "neon.h"

void	ft_keydown_handler(t_game *game, int key)
{
	if (key == SDLK_UP)
		ft_move_forward(game);
	if (key == SDLK_DOWN)
		ft_move_backward(game);
	if (key == SDLK_RIGHT)
		ft_turn_right(game);
	if (key == SDLK_LEFT)
		ft_turn_left(game);
	if (key == SDLK_q)
		game->texture_compasing = !game->texture_compasing;
	if (key == SDLK_ESCAPE)
		game->running = 0;
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
			if (event.key.keysym.sym == SDLK_RIGHT ||
				event.key.keysym.sym == SDLK_LEFT)
				game->st_wheel_pos = 1;
			// if (event.key.keysym.sym == SDLK_UP)
			// 	game->moto.acc_input = 0;
		}
	}
}
