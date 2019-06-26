/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:55:37 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/26 21:52:31 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "neon.h"

void	ft_update(t_game *game, int dt)
{
	// ft_ride(game, &(game->moto), dt);
	dt++;
	ft_create_skybox(game);
	caster(game);
}
