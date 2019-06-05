/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 19:30:33 by mhonchar          #+#    #+#             */
/*   Updated: 2019/05/23 17:56:07 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D
# define WOLF3D

# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <math.h>
# include <time.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"

# define WIDTH 640
# define HEIGHT 480
# define TEXWIDTH 64
# define TEXHEIGHT 64
# define mapWidth 24
# define mapHeight 24
# define NUMBER_OF_TEXTURES 8
# define THREADS_AMOUNT 4
# define K_MOUSE_LEFT 1
# define K_MOUSE_RIGHT 2
# define K_MOUSE_WHEEL_DOWN 4
# define K_MOUSE_WHEEL_UP 5
# define K_LEFT_ARROW 123
# define K_RIGTH_ARROW 124
# define K_UP_ARROW 126
# define K_DOWN_ARROW 125
# define K_NUM_PLUS 69
# define K_NUM_MINUS 78
# define K_NUM_0 82

# define K_NUM_7 89
# define K_NUM_4 86
# define K_NUM_8 91
# define K_NUM_6 88
# define K_NUM_2 84
# define K_NUM_9 92
# define K_NUM_3 85
# define K_NUM_1 83

# define K_1 18
# define K_2 19
# define K_3 20
# define K_4 21
# define K_5 23
# define K_6 22
# define K_7 26
# define K_8 28

# define K_ESC 53
# define K_SPACEBAR 49
# define K_H 4
# define K_R 15
# define K_G 5
# define K_B 11
# define K_L 37
# define K_I 34

# define E_NOFILE -2
# define E_EMPTY_FILE -3
# define E_BAD_MAP -4

# define C_RED 0xFF0000
# define C_GREEN 0x00FF00
# define C_BLUE 0x0000FF
# define C_WHITE 0xFFFFFF
# define C_YELLOW 0xD8CE0F

typedef struct	s_vector3
{
	int			x;
	int			y;
	int			z;
	int			color;
}				t_vector3;

typedef struct	s_vector2
{
	int			x;
	int			y;
}				t_vector2;

typedef struct	s_map
{
	int			**data;
	int			width;
	int			height;
}				t_map;

typedef struct		s_win
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*pix_ptr;
	t_map		map;
	t_vector2	pos;
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	double		currTime;
	double		oldTime;
	double		cameraX;
	double		rayDirX;
	double		rayDirY;
	double		moveSpeed;
	double		rotSpeed;
	unsigned int	buffer[HEIGHT][WIDTH];
	int			**textures;

}					t_win;

int			ft_len_2darr(char **arr);
void		ft_del_list(t_list **lst);
void		ft_free_2darr(char **arr);
int			ft_read_map(t_win *win, char *fname);

void		ft_draw_verline(t_win *win, int x, int y1, int y2, int color);
void		ft_render_view(t_win *win);
void		ft_render_view(t_win *win);
void		generate_textures(t_win *win);
void		ft_pp_img(char *pixels, int x, int y, int color);

#endif
