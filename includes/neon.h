/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neon.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 16:48:35 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/23 18:42:20 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEON_H
# define NEON_H

# include "SDL.h"
# include "SDL_image.h"
# include "libft.h"
# include "get_next_line.h"
# include <math.h>
# define SCR_WIDTH 800
# define SCR_HEIGHT 600
# define TEXWIDTH 64
# define TEXHEIGHT 64
# define TEX_NUM 8

/*
**	World block size
*/
# define WB_SIZE 64
# define DEG_TO_RAD(angle) (M_PI * (angle)) / 180
# define MIN(a,b) ((a) < (b) ? (a) : (b))
# define MAX(a,b) ((a) > (b) ? (a) : (b))

# define E_NOFILE -2
# define E_EMPTY_FILE -3
# define E_BAD_MAP -4



typedef struct		s_vector2
{
	double				x;
	double				y;
}					t_vector2;

typedef struct		s_ivector2
{
	int				x;
	int				y;
}					t_ivector2;

typedef struct		s_vector3
{
	float			x;
	float			y;
	float			z;
}					t_vector3;

typedef struct		s_timer
{
	int				oldtime;
	int				currtime;
}					t_timer;

typedef struct		s_raycaster
{
	int				hit;
	int				side;
	double			wall_dist;
	t_vector2		cam;
	t_vector2		ray_dir;
	t_ivector2		map_coord;
	t_vector2		side_dist;
	t_vector2		delta_dist;
	t_ivector2		step;
}					t_raycaster;

typedef struct	s_texturer
{
	int			tex_num;
	int			tex_hit;
	double		wall_hit;
	int			draw_start;
	int			draw_end;
	int			line_height;

}				t_texturer;

/*
**	Contains player information
**	pos: player position on map
**	dir: direction vector of player which means where player looking
*/	
typedef struct		s_player
{
	double			move_speed;
	double			rot_speed;
	t_vector2		pos;
	t_vector2		dir;
	int				height;
}					t_player;

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
	SDL_Texture 	*scr_tex;
	SDL_Surface		*scr_surf;
	SDL_Surface 	*surfaces[TEX_NUM];
	t_timer			timer;
	t_player		player;
	t_map			map;
	t_vector2		plane;
	int				running;
	int				**textures;
	
}					t_game;




int			ft_len_2darr(char **arr);
void		ft_del_list(t_list **lst);
void		ft_free_2darr(char **arr);
int			ft_file_review(const char *fname);
int			ft_read_map(t_game *game, const char *fname);

void		ft_event_handler(t_game *game);
void		ft_update(t_game *game);
void		ft_render(t_game *game);
void		ft_clean(t_game *game);
void		ft_game_init(t_game *game);
void		caster(t_game *game);

/** **************************************
**	************ Movement ****************
*****************************************/
void		ft_move_forward(t_game *game);
void		ft_move_backward(t_game *game);
void		ft_turn_left(t_game *game);
void		ft_turn_right(t_game *game);

/** **************************************
**	**** SDL special functions ***********
*****************************************/
void		ft_put_pixel32(SDL_Surface *surface, int x, int y, Uint32 pixel);
Uint32		ft_get_pixel32(SDL_Surface *surface, int x, int y);


#endif
