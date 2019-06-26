/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:48:12 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/26 19:39:35 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "neon.h"

void	ft_clean(t_game *game)
{
	int		i;

	i = -1;
	while (++i < TEX_NUM)
		SDL_FreeSurface(game->surfaces[i]);
	i = -1;
	while (++i < 3)
		SDL_DestroyTexture(game->steering[i]);
	SDL_FreeSurface(game->scr_surf);
	SDL_FreeSurface(game->ceiling);
	TTF_CloseFont(game->font);
	SDL_DestroyWindow(game->win);
	SDL_DestroyRenderer(game->renderer);
	Mix_FreeMusic(game->background_sound);
	TTF_Quit();
	Mix_CloseAudio();
	SDL_Quit();
	ft_free_2darr((char**)(game->map.data));
	ft_putendl("GG");
}
