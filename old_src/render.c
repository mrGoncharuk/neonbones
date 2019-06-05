/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 17:49:24 by mhonchar          #+#    #+#             */
/*   Updated: 2019/05/23 17:56:11 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_texturing(t_win *win, int x)
{
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
		
		ft_texturing(win, x);

	}
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
}

/*
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
			if (worldMap[mapX][mapY] > 0) hit = 1;
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
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if(drawEnd >= HEIGHT)drawEnd = HEIGHT - 1;
			     //choose wall color
		int color;
		switch(worldMap[mapX][mapY])
		{
			case 1:  color = C_RED;  break; //red
			case 2:  color = C_GREEN;  break; //green
			case 3:  color = C_BLUE;   break; //blue
			case 4:  color = C_WHITE;  break; //white
			default: color = C_YELLOW; break; //yellow
    	}

		//give x and y sides different brightness
		if (side == 1) {color = color / 2;}

		//draw the pixels of the stripe as a vertical line
		ft_draw_verline(win, x, drawStart, drawEnd, color);
    }

    //timing for input and FPS counter
	// win->oldTime = win->currTime;
    // win->currTime = (double)time(NULL);
    // double frameTime = (win->currTime - win->oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
    // mlx_string_put(win->mlx_ptr, win->win_ptr, 5, 5, C_GREEN, ft_itoa(1.0 / frameTime));

    //speed modifiers
    // double moveSpeed = 0.00000; //the constant value is in squares/second
    // double rotSpeed = 0.000003; //the constant value is in radians/second
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
}*/
