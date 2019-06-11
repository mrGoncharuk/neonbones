#include "neon.h"

void	ft_game_init(t_game *game)
{
	game->player.camera = 0;
	game->raycaster.fov = 60;
	game->player.height = WB_SIZE / 2;
}