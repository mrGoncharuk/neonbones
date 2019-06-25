/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:48:12 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/25 20:57:15 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "neon.h"

void	ft_clean(t_game *game)
{
	int		i;

	i = -1;
	while (++i < TEX_NUM)
		SDL_FreeSurface(game->surfaces[i]);
	SDL_FreeSurface(game->scr_surf);
	SDL_FreeSurface(game->ceiling);
	TTF_CloseFont(game->font);
	SDL_DestroyWindow(game->win);
	SDL_DestroyRenderer(game->renderer);
	TTF_Quit();
	SDL_Quit();
	ft_free_2darr((char**)(game->map.data));
	ft_putendl("GG");
}
