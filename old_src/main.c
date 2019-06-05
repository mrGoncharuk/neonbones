/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 19:29:26 by mhonchar          #+#    #+#             */
/*   Updated: 2019/05/23 14:56:10 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

int		ft_deal_key(int key, void *param)
{
	t_win	*win;

	win = (t_win *)param;
	if (key == K_ESC)
	{
		system("leaks Wolf3D");
		exit(0);
	}
	if (key == K_UP_ARROW)
	{
		if (win->map.data[(int)(win->posX + win->dirX * win->moveSpeed)][(int)(win->posY)] == 0)
			win->posX += win->dirX * win->moveSpeed;
			if (win->map.data[(int)(win->posX)][(int)(win->posY + win->dirY * win->moveSpeed)] == 0)
			win->posY += win->dirY * win->moveSpeed;
	}
	if (key == K_DOWN_ARROW)
	{
		if (win->map.data[(int)(win->posX - win->dirX * win->moveSpeed)][(int)(win->posY)] == 0)
			win->posX -= win->dirX * win->moveSpeed;
			if (win->map.data[(int)(win->posX)][(int)(win->posY - win->dirY * win->moveSpeed)] == 0)
			win->posY -= win->dirY * win->moveSpeed;
	}
	if (key == K_RIGTH_ARROW)
	{
		double oldDirX;
		oldDirX = win->dirX;
		win->dirX = win->dirX * cos(-win->rotSpeed) - win->dirY * sin(-win->rotSpeed);
		win->dirY = oldDirX * sin(-win->rotSpeed) + win->dirY * cos(-win->rotSpeed);
		double oldPlaneX;
		oldPlaneX = win->planeX;
		win->planeX = win->planeX * cos(-win->rotSpeed) - win->planeY * sin(-win->rotSpeed);
		win->planeY = oldPlaneX * sin(-win->rotSpeed) + win->planeY * cos(-win->rotSpeed);
	}
	if (key == K_LEFT_ARROW)
	{
		double oldDirX;
		oldDirX = win->dirX;
		win->dirX = win->dirX * cos(win->rotSpeed) - win->dirY * sin(win->rotSpeed);
		win->dirY = oldDirX * sin(win->rotSpeed) + win->dirY * cos(win->rotSpeed);
		double oldPlaneX;
		oldPlaneX = win->planeX;
		win->planeX = win->planeX * cos(win->rotSpeed) - win->planeY * sin(win->rotSpeed);
		win->planeY = oldPlaneX * sin(win->rotSpeed) + win->planeY * cos(win->rotSpeed);
	}
	ft_bzero(win->pix_ptr, WIDTH * HEIGHT * 4);
	ft_render_view(win);
	return (0);
}

void	ft_render_view(t_win *win)
{
	for(int x = 0; x < WIDTH; x++)
	{
		//calculate ray position and direction
		win->cameraX = 2 * x / (double)WIDTH - 1; //x-coordinate in camera space
		win->rayDirX = win->dirX + win->planeX * win->cameraX;
		win->rayDirY = win->dirY + win->planeY * win->cameraX;

		//which box of the map we're in
		int mapX = (int)win->posX;
		int mapY = (int)win->posY;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = ft_abs(1 / win->rayDirX);
		double deltaDistY = ft_abs(1 / win->rayDirY);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

					//calculate step and initial sideDist
		if (win->rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (win->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - win->posX) * deltaDistX;
		}
		if (win->rayDirY < 0)
		{
			stepY = -1;
				sideDistY = (win->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - win->posY) * deltaDistY;
		}
		
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if ( win->map.data[mapX][mapY] > 0) 
				hit = 1;
		} 

		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (side == 0)
			perpWallDist = (mapX - win->posX + (1 - stepX) / 2) / win->rayDirX;
		else
			perpWallDist = (mapY - win->posY + (1 - stepY) / 2) / win->rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(HEIGHT / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if(drawStart < 0)
			drawStart = 0;
		
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if(drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;
					//choose wall color
		

		//texturing calculations
		int texNum =  win->map.data[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!	
		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (side == 0)
			wallX = win->posY + perpWallDist * win->rayDirY;
		else
			wallX = win->posX + perpWallDist * win->rayDirX;
		wallX -= floor((wallX));
		//x coordinate on the texture
		int texX = (int)(wallX * (double)(TEXWIDTH));
		if (side == 0 && win->rayDirX > 0)
			texX = TEXWIDTH - texX - 1;
		if (side == 1 && win->rayDirY < 0)
			texX = TEXWIDTH - texX - 1;

		for(int y = drawStart; y<drawEnd; y++)
		{
			int d = y * 256 - HEIGHT * 128 + lineHeight * 128;  //256 and 128 factors to avoid floats
			// TODO: avoid the division to speed this up
			int texY = ((d * TEXHEIGHT) / lineHeight) / 256;
			unsigned int color = win->textures[texNum][TEXHEIGHT * texY + texX];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if (side == 1) 
				color = (color >> 1) & 8355711;
			ft_pp_img(win->pix_ptr, x, y, color);

		}
	}
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
}

void	ft_init_win(t_win *win)
{
	int		bpp;
	int		size_line;
	int		endian;

	bpp = 32;
	size_line = WIDTH;
	endian = 0;
	win->mlx_ptr = mlx_init();
	win->win_ptr = mlx_new_window(win->mlx_ptr, WIDTH, HEIGHT, "Wolf3D");
	win->img_ptr = mlx_new_image(win->mlx_ptr, WIDTH, HEIGHT);
	win->pix_ptr = mlx_get_data_addr(win->img_ptr, &bpp, &size_line, &endian);
}

int		main(int argc, char **argv)
{
	t_win		win;
	int			ret;
	
	if (argc != 2)
	{
		(void)argv;
		write(1, "lol\n", 4);
		return (0);
	}
	if ((ret = ft_read_map(&win, argv[1])) < 0)
	{
		printf ("Error code: %d\n", ret);
		system("leaks Wolf3D");
		return (0);
	}
	win.dirX = -1;
	win.dirY = 0;
	win.planeX = 0;
	win.planeY = 0.66;
	win.currTime = 0;
	win.oldTime = 0;
	win.moveSpeed = 0.25; //the constant value is in squares/second
	win.rotSpeed = 0.1; //the constant value is in radians/second
	win.textures = (int **)malloc(NUMBER_OF_TEXTURES * sizeof(int *));


	generate_textures(&win);
	ft_init_win(&win);
	ft_render_view(&win);
	mlx_hook(win.win_ptr, 2, 0, ft_deal_key, (void*)&win);
	//mlx_key_hook(win.win_ptr, ft_deal_key, (void*)&win);
	mlx_loop(win.mlx_ptr);
	return (0);
}
