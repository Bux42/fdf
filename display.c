/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 23:45:24 by videsvau          #+#    #+#             */
/*   Updated: 2017/06/01 15:13:52 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clear_image(t_m *mlx)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < HEIGHT)
	{
		while (y < WIDTH)
		{
			put_pixel(mlx, x, y, 0x00000000);
			y++;
		}
		y = 0;
		x++;
	}
}

void	center_grid(t_m **mlxx)
{
	t_m		*m;
	int		x;
	int		y;

	m = *mlxx;
	x = -1;
	while (++x < m->height)
	{
		y = -1;
		while (++y < m->width)
		{
			m->l[x][y].prx -= m->decx + m->spx;
			m->l[x][y].pry -= m->decy + m->spy;
		}
	}
}

void	prepare_grid(t_m **mlxx)
{
	int		x;
	int		y;
	t_m		*m;

	m = *mlxx;
	x = -1;
	while (++x < m->height)
	{
		y = -1;
		while (++y < m->width)
		{
			m->l[x][y].px = 1000 + (x * m->sp);
			m->l[x][y].py = 1000 + (y * m->sp);
			rotation(&m->l[x][y], m);
		}
	}
	m->decx = m->l[m->midmx][m->midmy].prx - m->midx;
	m->decy = m->l[m->midmx][m->midmy].pry - m->midy;
	center_grid(mlxx);
}

void	draw_grid(t_m **mlxx)
{
	int		x;
	int		y;
	t_m		*m;

	m = *mlxx;
	x = -1;
	m->stp[1] = WIDTH - m->sp + m->spy;
	m->stp[0] = WIDTH - m->sp + m->spx;
	degree_to_rad(&m->rot);
	prepare_grid(&m);
	m->color = m->scolor;
	clear_image(m);
	while (++x < m->height)
	{
		y = -1;
		while (++y < m->width)
		{
			if (y < m->width - 1)
				draw_right(m, m->l[x][y], m->l[x][y + 1]);
			if (x < m->height - 1)
				draw_down(m, m->l[x][y], m->l[x + 1][y]);
		}
	}
	mlx_put_image_to_window(m->ptr, m->win, m->img, 0, 0);
}
