#include "neon.h"

void	ft_sdl_init(t_game* game)
{
	SDL_Init(SDL_INIT_VIDEO);
	game->win = SDL_CreateWindow("NeonBone$$$", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_OPENGL);
	game->renderer = SDL_CreateRenderer(game->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}
void	ft_game_init(t_game *game)
{
	ft_sdl_init(game);
	game->player.camera = 0;
	game->raycaster.fov = 60;
	game->player.height = WB_SIZE / 2;
}
