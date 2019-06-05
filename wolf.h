
#ifndef WOLF_H
# define WOLF_H

# include <SDL.h>

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

typedef struct		s_player
{
	t_vector2		pos;
	t_vector2		dir;
}					t_player;

typedef  struct		s_raycaster
{
	t_vector2		camera;
	t_vector2		raydir;

}					t_raycaster;


typedef struct		s_game
{
	SDL_Window*		win;
	SDL_Event		event;
	SDL_Renderer*	renderer;

	t_raycaster		raycaster;
	t_player		player;
	t_timer			timer;

}					t_game;

#endif
