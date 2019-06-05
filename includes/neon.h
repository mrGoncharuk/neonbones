/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neon.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 16:48:35 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/05 17:13:30 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEON_H
# define NEON_H

# include <SDL2/SDL.h>

# define SCR_WIDTH 800
# define SCR_HEIGHT 600

typedef struct		s_vector2
{
	float			x;
	float			y;
}					t_vector2;

typedef struct		s_vector3
{
	float			x;
	float			y;
	float			z;
}					t_vector3;

typedef struct		s_timer
{
	float			oldtime;
	float			currtime;
}					t_timer;

/*
**	Contains player information
**	pos: player position on map
**	dir: direction vector of player which means where player looking
*/	
typedef struct		s_player
{
	t_vector2		pos;
	t_vector2		dir;
}					t_player;

/*
**	Contains raycasting information
**	plane: the 2d raycaster version of camera plane
**	raydir: direction vector of ray which sends on several points of FOV
**	camera: coordinate in camera space
*/	
typedef struct		s_raycaster
{
	t_vector2		plane;
	t_vector2		raydir;
	float			camera;

}					t_raycaster;

typedef struct		s_game
{
	SDL_Window		*win;
	SDL_Event		event;
	SDL_Renderer	*renderer;

	t_raycaster		raycaster;
	t_player		player;
	t_timer			timer;

}					t_game;

#endif
