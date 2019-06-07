/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neon.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 16:48:35 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/07 20:19:44 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEON_H
# define NEON_H

# include "SDL.h"
# include "libft.h"
# include "get_next_line.h"
# include <math.h>
# define SCR_WIDTH 800
# define SCR_HEIGHT 600
/*
**	World block size
*/

# define DEG_TO_RAD(angle) (M_PI * (angle)) / 180

# define WB_SIZE 64
# define E_NOFILE -2
# define E_EMPTY_FILE -3
# define E_BAD_MAP -4

typedef struct		s_vector2
{
	int				x;
	int				y;
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
	float			camera;
	int				height;
}					t_player;

/*
**	Contains raycasting information
**	plane: the 2d raycaster version of camera plane
**	raydir: direction vector of ray which sends on several points of FOV
**	camera: coordinate in camera space
*/	
typedef struct		s_raycaster
{


	float			fov;


}					t_raycaster;

typedef struct		s_map
{
	int				**data;
	int				width;
	int				height;
}					t_map;



typedef struct		s_game
{
	SDL_Window		*win;
	SDL_Event		event;
	SDL_Renderer	*renderer;

	t_raycaster		raycaster;
	t_player		player;
	t_map			map;
	t_timer			timer;

}					t_game;


int			ft_len_2darr(char **arr);
void		ft_del_list(t_list **lst);
void		ft_free_2darr(char **arr);
int			ft_read_map(t_game *game, char *fname);

#endif
