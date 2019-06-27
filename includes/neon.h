/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neon.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 16:48:35 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/27 21:02:59 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEON_H
# define NEON_H

# include "SDL.h"
# include "SDL_image.h"
# include "SDL_ttf.h"
# include "SDL_mixer.h"
# include "libft.h"
# include "get_next_line.h"
# include <math.h>
# define SCR_WIDTH 800
# define SCR_HEIGHT 600
# define TEXWIDTH 512
# define TEXHEIGHT 512
# define TEX_NUM 15

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
	double			x;
	double			y;
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

typedef struct		s_fps
{
	Uint32			startclock;
	Uint32			deltaclock;
	Uint32			currentfps;
}					t_fps;

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

typedef struct		s_texturer
{
	int				tex_num;
	int				tex_hit;
	double			wall_hit;
	int				draw_start;
	int				draw_end;
	int				line_height;

}					t_texturer;

typedef struct		s_floorcaster
{
	int				x;
	int				floor_texx;
	int				floor_texy;
	double			floor_wallx;
	double			floor_wally;
	double			wall_dist;
	double			player_dist;
	double			curr_dist;
	double			curr_floorx;
	double			curr_floory;
}					t_floorcaster;

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

typedef struct		s_vehicle
{
	float			speed;
	float			power;
	float			friction;
	int				forward;
	int				backward;
	int				left;
	int				right;
}					t_vehicle;

typedef struct		s_map
{
	int				**data;
	int				width;
	int				height;
}					t_map;

typedef struct		s_game
{
	SDL_Window		*win;
	TTF_Font		*font;
	SDL_Event		event;
	SDL_Renderer	*renderer;
	SDL_Texture		*scr_tex;
	SDL_Surface		*scr_surf;
	SDL_Surface		*surfaces[TEX_NUM + 1];
	SDL_Surface		*ceiling;
	SDL_Surface		*notile;
	SDL_Texture		*steering[3];
	int				st_wheel_w;
	int				st_wheel_h;
	int				st_wheel_pos;
	SDL_Texture		*text_tex;
	SDL_Rect		text_rect;
	Mix_Music		*background_sound;
	t_fps			fps;
	t_player		player;
	t_map			map;
	t_vehicle		moto;
	t_vector2		plane;
	int				running;
	int				**textures;
	int				skybox_ori;
	int				texture_compasing;
}					t_game;

int					ft_get_rand_tile(void);
int					ft_len_2darr(char **arr);
void				ft_del_list(t_list **lst);
void				ft_free_2darr(char **arr);
int					ft_file_review(const char *fname);
int					ft_check_map_textures(t_game *game);
int					ft_read_map(t_game *game, const char *fname);
void				ft_event_handler(t_game *game);
void				ft_update(t_game *game);
void				ft_render(t_game *game);
void				ft_clean(t_game *game);
int					ft_game_init(t_game *game);
void				ft_std_init(t_game *game);
void				ft_load_tiles(t_game *game);

/*
****************************************
************ Ray Casting ***************
****************************************
*/
void				caster(t_game *game);
void				ft_calc_initial(t_raycaster *rc, t_game *game, int x);
void				ft_set_steps(t_raycaster *rc, t_player *player);
void				ft_calc_dist(t_raycaster *rc, t_game *game);
void				ft_texturing_calc(t_game *game, t_raycaster *rc,
									t_texturer *tex);
void				ft_texturing_walls(t_game *game, t_raycaster *rc,
									t_texturer *tex, int x);
void				ft_floor_caster(t_game *game, t_raycaster *rc,
									t_texturer *tex, t_floorcaster *fc);
void				ft_set_wall_dir(t_floorcaster *fc, t_raycaster *rc,
									t_texturer *tex);
void				ft_draw_ceiling(t_game *game, t_texturer *tex,
									t_floorcaster *fc, int x);
void				ft_draw_floor(t_game *game, t_texturer *tex,
									t_floorcaster *fc, int x);
void				ft_create_skybox(t_game *game);
void				ft_select_texture(t_raycaster *rc, t_texturer *tex);

/*
****************************************
************** Movement ****************
****************************************
*/
void				ft_move_forward(t_game *game);
void				ft_move_backward(t_game *game);
void				ft_turn_left(t_game *game);
void				ft_turn_right(t_game *game);
void				ft_ride(t_game *game, t_vehicle *moto, int dt);
void				ft_init_vehicle(t_vehicle *moto);

/*
******************************************
******** SDL special functions ***********
******************************************
*/
void				ft_put_pixel32(SDL_Surface *surface, int x, int y,
									Uint32 pixel);
Uint32				ft_get_pixel32(SDL_Surface *surface, int x, int y);
void				ft_create_fps_tex(t_game *game, char *fps);
int					sdl_texture_manager(SDL_Renderer *renderer,
										SDL_Texture **tex, const char *tname);

#endif
