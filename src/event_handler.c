/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:30:21 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/25 20:01:23 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "neon.h"

void	ft_event_handler(t_game *game)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			game->running = 0;
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_UP)
				ft_move_forward(game);
			if (event.key.keysym.sym == SDLK_DOWN)
				ft_move_backward(game);
			if (event.key.keysym.sym == SDLK_RIGHT)
				ft_turn_right(game);
			if (event.key.keysym.sym == SDLK_LEFT)
				ft_turn_left(game);
			if (event.key.keysym.sym == SDLK_q)
				game->texture_compasing = !game->texture_compasing;
			if (event.key.keysym.sym == SDLK_ESCAPE)
				game->running = 0;
		}
	}
}
