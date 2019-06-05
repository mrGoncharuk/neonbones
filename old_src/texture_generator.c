/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_generator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 16:45:08 by mhonchar          #+#    #+#             */
/*   Updated: 2019/05/23 14:40:56 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	generate_textures(t_win *win)
{
	int		x;
	int		y;

	x = -1;
	while (++x < NUMBER_OF_TEXTURES)
		win->textures[x] = (int *)malloc(TEXHEIGHT * TEXHEIGHT * sizeof(int));
	x = -1;
	while (++x < TEXWIDTH)
	{
		y = -1;
		while (++y < TEXHEIGHT)
		{
			int xorcolor = (x * 256 / TEXWIDTH) ^ (y * 256 / TEXHEIGHT);
			//int xcolor = x * 256 / texWidth;
			int ycolor = y * 256 / TEXHEIGHT;
			int xycolor = y * 128 / TEXHEIGHT + x * 128 / TEXWIDTH;
			win->textures[0][TEXWIDTH * y + x] = 65536 * 254 * (x != y && x != TEXWIDTH - y); //flat red texture with black cross
			win->textures[1][TEXWIDTH * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
			win->textures[2][TEXWIDTH * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
			win->textures[3][TEXWIDTH * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
			win->textures[4][TEXWIDTH * y + x] = 256 * xorcolor; //xor green
			win->textures[5][TEXWIDTH * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
			win->textures[6][TEXWIDTH * y + x] = 65536 * ycolor; //red gradient
			win->textures[7][TEXWIDTH * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
		}
	}
}
