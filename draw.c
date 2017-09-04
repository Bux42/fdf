/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 09:13:22 by videsvau          #+#    #+#             */
/*   Updated: 2017/05/21 20:49:11 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		max_diff(t_m *m)
{
	int		min;
	int		max;
	int		x;
	int		y;

	min = 2147483647;
	max = -2147483647;
	x = 0;
	while (x < m->height)
	{
		y = 0;
		while (y < m->width)
		{
			if (m->l[x][y].v > max)
				max = m->l[x][y].v;
			if (m->l[x][y].v < min)
				min = m->l[x][y].v;
			y++;
		}
		x++;
	}
	return ((max - min) + 1);
}

int		nbpx(int x0, int y0, int x1, int y1)
{
	int		dist1;
	int		dist2;

	dist1 = abs(x1 - x0) + 1;
	dist2 = abs(y1 - y0) + 1;
	if (dist1 >= dist2)
		return (dist1);
	return (dist2);
}

void	put_pixel(t_m *m, int x, int y, int color)
{
	if (x + 1 <= HEIGHT && y + 1 <= WIDTH && x >= 0 && y >= 0)
		*(unsigned *)(m->imga + m->sl * y + (m->bpp / 8) * x) = color;
}

void	value(t_l line1, t_l line2, int values[6])
{
	values[0] = abs(line2.prx - line1.prx);
	values[1] = line1.prx < line2.prx ? 1 : -1;
	values[2] = abs(line2.pry - line1.pry);
	values[3] = line1.pry < line2.pry ? 1 : -1;
	values[4] = (values[0] > values[2] ? values[0] : -values[2]) / 2;
	values[6] = 0;
}

void	draw_line(t_l line1, t_l line2, t_m *m)
{
	int	values[7];

	value(line1, line2, values);
	while (1)
	{
		if (++values[6] % m->colorinterval == 0 && m->color < m->scolor + 254)
			m->color += m->colorchange;
		put_pixel(m, line1.prx, line1.pry, m->color);
		if (line1.prx == line2.prx && line1.pry == line2.pry)
			break ;
		values[5] = values[4];
		if (values[5] > -values[0])
		{
			values[4] -= values[2];
			line1.prx += values[1];
		}
		if (values[5] < values[2])
		{
			values[4] += values[0];
			line1.pry += values[3];
		}
	}
	m->color = m->scolor;
}
