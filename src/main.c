/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 16:48:24 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/28 16:02:00 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "neon.h"

void	ft_mainloop(t_game *game)
{
	const int	frame_delay = 1000 / 60;

	Mix_PlayMusic(game->background_sound, 1);
	while (game->running)
	{
		game->fps.startclock = SDL_GetTicks();
		ft_event_handler(game);
		ft_update(game);
		ft_create_fps_tex(game, ft_itoa(game->fps.currentfps));
		ft_render(game);
		game->fps.deltaclock = SDL_GetTicks() - game->fps.startclock;
		game->fps.startclock = SDL_GetTicks();
		if (game->fps.deltaclock != 0)
			game->fps.currentfps = 1000 / game->fps.deltaclock;
		if (frame_delay > game->fps.deltaclock)
			SDL_Delay(frame_delay - game->fps.deltaclock);
	}
	ft_clean(game);
}

int		main(int argc, char **argv)
{
	t_game		game;
	int			ret;

	if (argc != 2)
	{
		ft_putendl("Usage: ./NeonBones maps/[map_name]");
		return (0);
	}
	if ((ret = ft_read_map(&game, argv[1]) < 0))
	{
		ft_putstr("Error code: ");
		ft_putnbr(ret);
		ft_putchar('\n');
		return (0);
	}
	if (ft_game_init(&game) < 0)
	{
		ft_putstr("Error while game initialization");
		ft_putchar('\n');
		return (-1);
	}
	ft_mainloop(&game);
	return (0);
}
