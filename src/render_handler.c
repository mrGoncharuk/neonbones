/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:46:31 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/27 21:01:53 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "neon.h"

void	ft_create_fps_tex(t_game *game, char *fps)
{
	char		text[50];
	SDL_Color	color;
	SDL_Surface	*txt_s;

	color = (SDL_Color) {255, 255, 255, 255};
	ft_strcpy(text, "FPS: ");
	ft_strcpy(text + 5, fps);
	free(fps);
	txt_s = TTF_RenderText_Solid(game->font, text, color);
	if (txt_s == NULL)
		ft_putendl("Unable to render text surface!");
	else
	{
		game->text_tex = SDL_CreateTextureFromSurface(game->renderer, txt_s);
		if (game->text_tex == NULL)
			ft_putendl("Unable to create texture from rendered text!");
		else
		{
			game->text_rect.h = txt_s->h;
			game->text_rect.w = txt_s->w;
			game->text_rect.x = 0;
			game->text_rect.y = 0;
			SDL_FreeSurface(txt_s);
		}
	}
}

void	wipe_surface(SDL_Surface *surface)
{
	SDL_LockSurface(surface);
	SDL_memset(surface->pixels, 0, surface->h * surface->pitch);
	SDL_UnlockSurface(surface);
}

void	ft_render_steering_bar(t_game *game)
{
	SDL_RenderCopy(game->renderer, game->steering[game->st_wheel_pos], NULL,
			&((SDL_Rect){SCR_WIDTH / 2 - game->st_wheel_w / 6,
						SCR_HEIGHT / 2 + game->st_wheel_h / 10,
						game->st_wheel_w / 3,
						game->st_wheel_h / 3}));
}

void	ft_render(t_game *game)
{
	SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
	SDL_RenderClear(game->renderer);
	game->scr_tex = SDL_CreateTextureFromSurface(game->renderer,
		game->scr_surf);
	SDL_RenderCopy(game->renderer, game->scr_tex, NULL, NULL);
	SDL_RenderCopy(game->renderer, game->text_tex, NULL, &(game->text_rect));
	ft_render_steering_bar(game);
	wipe_surface(game->scr_surf);
	SDL_DestroyTexture(game->text_tex);
	SDL_DestroyTexture(game->scr_tex);
	SDL_RenderPresent(game->renderer);
}
