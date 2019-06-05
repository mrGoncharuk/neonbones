/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 18:00:18 by mhonchar          #+#    #+#             */
/*   Updated: 2019/05/21 15:11:37 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_pp_img(char *pixels, int x, int y, int color)
{
	if ((x >= 0 && x < WIDTH) && (y >= 0 && y < HEIGHT))
		*(int *)(pixels + (WIDTH * y + x) * 4) = color;
}

void		ft_draw_low_line(t_win *win, t_vector3 p0, t_vector3 p1,
			t_vector3 deltap)
{
	t_vector3		p;
	int				d;
	int				yi;

	yi = 1;
	if (deltap.y < 0)
	{
		yi = -1;
		deltap.y = -deltap.y;
	}
	d = 2 * deltap.y - deltap.x;
	p.y = p0.y;
	p.x = p0.x;
	while (p.x <= p1.x)
	{
		ft_pp_img(win->pix_ptr, p.x, p.y, p0.color);
		if (d > 0)
		{
			p.y += yi;
			d -= 2 * deltap.x;
		}
		d += 2 * deltap.y;
		p.x++;
	}
}

void		ft_draw_high_line(t_win *win, t_vector3 p0, t_vector3 p1,
			t_vector3 deltap)
{
	t_vector3		p;
	int				d;
	int				xi;

	xi = 1;
	if (deltap.x < 0)
	{
		xi = -1;
		deltap.x = -deltap.x;
	}
	d = 2 * deltap.x - deltap.y;
	p.y = p0.y;
	p.x = p0.x;
	while (p.y <= p1.y)
	{
		ft_pp_img(win->pix_ptr, p.x, p.y, p0.color);
		if (d > 0)
		{
			p.x = p.x + xi;
			d = d - 2 * deltap.y;
		}
		d = d + 2 * deltap.x;
		p.y++;
	}
}

t_vector3	ft_calc_delta(t_vector3 p0, t_vector3 p1)
{
	t_vector3	deltap;

	deltap.x = p1.x - p0.x;
	deltap.y = p1.y - p0.y;
	return (deltap);
}

void		ft_draw_line_img(t_win *win, t_vector3 p0, t_vector3 p1)
{
	if (abs(p1.y - p0.y) < abs(p1.x - p0.x))
	{
		if (p0.x > p1.x)
			ft_draw_low_line(win, p1, p0, ft_calc_delta(p1, p0));
		else
			ft_draw_low_line(win, p0, p1, ft_calc_delta(p0, p1));
	}
	else
	{
		if (p0.y > p1.y)
			ft_draw_high_line(win, p1, p0, ft_calc_delta(p1, p0));
		else
			ft_draw_high_line(win, p0, p1, ft_calc_delta(p0, p1));
	}
}

void	ft_draw_verline(t_win *win, int x, int y1, int y2, int color)
{
	t_vector3	p0;
	t_vector3	p1;

	p0.x = x;
	p0.y = y1;
	p1.x = x;
	p1.y = y2;
	p0.color = color;
	ft_draw_line_img(win, p0, p1);
}
