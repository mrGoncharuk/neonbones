/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_pixel_manipulation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 17:52:29 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/23 18:03:24 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"

Uint32	ft_get_pixel32(SDL_Surface *surface, int x, int y)
{
	int		bpp;
	Uint8	*p;

	bpp = surface->format->BytesPerPixel;
	p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	if (bpp == 1)
		return (*p);
	else if (bpp == 2)
		return (*(Uint16 *)p);
	else if (bpp == 3)
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return (p[0] << 16 | p[1] << 8 | p[2]);
		else
			return (p[0] | p[1] << 8 | p[2] << 16);
	}
	else if (bpp == 4)
		return (*(Uint32 *)p);
	else
		return (0);
}

void	ft_put_pixel32(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	Uint8	*p;

	p = (Uint8 *)surface->pixels + y * surface->pitch + x *
		surface->format->BytesPerPixel;
	if (surface->format->BytesPerPixel == 1)
		*p = pixel;
	else if (surface->format->BytesPerPixel == 2)
		*(Uint16 *)p = pixel;
	else if (surface->format->BytesPerPixel == 3)
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		{
			p[0] = (pixel >> 16) & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = pixel & 0xff;
		}
		else
		{
			p[0] = pixel & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = (pixel >> 16) & 0xff;
		}
	}
	else if (surface->format->BytesPerPixel == 4)
		*(Uint32 *)p = pixel;
}
