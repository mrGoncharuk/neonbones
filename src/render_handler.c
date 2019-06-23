/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:46:31 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/23 18:41:42 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "neon.h"

void	wipe_surface(SDL_Surface *surface)
{
	SDL_LockSurface(surface);
	SDL_memset(surface->pixels, 0, surface->h * surface->pitch);
	SDL_UnlockSurface(surface);
}

void	ft_render(t_game *game)
{
	SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
	SDL_RenderClear(game->renderer);
	caster(game);
	game->scr_tex = SDL_CreateTextureFromSurface(game->renderer,
		game->scr_surf);
	SDL_RenderCopy(game->renderer, game->scr_tex, NULL, NULL);
	wipe_surface(game->scr_surf);
	SDL_DestroyTexture(game->scr_tex);
	SDL_RenderPresent(game->renderer);
}
