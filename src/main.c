/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 16:48:24 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/23 18:42:27 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <time.h>
#include "neon.h"

void	ft_mainloop(t_game *game)
{
	while (game->running)
	{
		ft_event_handler(game);
		ft_update(game);
		ft_render(game);
	}
	ft_clean(game);
}

int		main(int argc, char **argv)
{
	t_game		game;
	int			ret;

	if (argc != 2)
	{
		(void)argv;
		ft_putendl("Bad arguments!");
		return (0);
	}
	if ((ret = ft_read_map(&game, argv[1]) < 0))
	{
		printf ("Error code: %d\n", ret);
		//system("leaks NeonBones");
		return (0);
	}
	ft_game_init(&game);
	ft_mainloop(&game);

	return (0);
}
