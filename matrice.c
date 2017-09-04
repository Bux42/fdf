/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 18:05:38 by videsvau          #+#    #+#             */
/*   Updated: 2017/06/01 15:13:23 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		draw_right(t_m *m, t_l line, t_l line2)
{
	m->colorchange = 0;
	m->colorinterval = 99999;
	m->nbp = nbpx(line.prx, line.pry, line2.prx, line2.pry);
	m->diff = abs(line.v - line2.v);
	m->palette = (255 * m->diff) / m->maxdiff;
	if (m->nbp >= m->palette && m->diff > 0)
	{
		m->colorinterval = m->nbp / m->palette;
		m->colorchange = 1;
	}
	else if (m->nbp < m->palette && m->diff > 0)
	{
		m->colorchange = m->palette / m->nbp;
		m->colorinterval = 1;
	}
	if (line.v <= line2.v)
	{
		m->color = m->scolor + (255 / m->maxdiff) * line.v;
		draw_line(line, line2, m);
	}
	if (line.v > line2.v)
	{
		m->color = m->scolor + (255 / m->maxdiff) * line2.v;
		draw_line(line2, line, m);
	}
}

void		draw_down(t_m *m, t_l line, t_l line2)
{
	m->colorchange = 0;
	m->colorinterval = 99999;
	m->nbp = nbpx(line.prx, line.pry, line2.prx, line2.pry);
	m->diff = abs(line.v - line2.v);
	m->palette = (255 / m->maxdiff) * m->diff;
	if (m->nbp >= m->palette && m->diff > 0)
	{
		m->colorinterval = m->nbp / m->palette;
		m->colorchange = 1;
	}
	else if (m->nbp < m->palette && m->diff > 0)
	{
		m->colorchange = m->palette / m->nbp;
		m->colorinterval = 1;
	}
	if (line.v <= line2.v)
	{
		m->color = m->scolor + (255 / m->maxdiff) * line.v;
		draw_line(line, line2, m);
	}
	if (line.v > line2.v)
	{
		m->color = m->scolor + (255 / m->maxdiff) * line2.v;
		draw_line(line2, line, m);
	}
}

void		rotate(int keycode, t_m *m)
{
	if (keycode == 13)
		m->rot.y += 10;
	if (keycode == 1)
		m->rot.y -= 10;
	if (keycode == 0)
		m->rot.x += 10;
	if (keycode == 2)
		m->rot.x -= 10;
	if (keycode == 12)
		m->rot.z -= 10;
	if (keycode == 14)
		m->rot.z += 10;
}

void		degree_to_rad(t_rot *rot)
{
	float	pi;

	pi = 3.1415;
	rot->ex = rot->x * (pi / 180);
	rot->ey = rot->y * (pi / 180);
	rot->ez = rot->z * (pi / 180);
}

void		rotation(t_l *l, t_m *m)
{
	l->prx = l->px;
	l->pry = l->py * cos(m->rot.ex) + (l->v * m->sp) * -sin(m->rot.ex);
	l->prz = l->py * sin(m->rot.ex) + (l->v * m->sp) * cos(m->rot.ex);
	l->px = l->prx * cos(m->rot.ey) + l->prz * sin(m->rot.ey);
	l->py = l->pry;
	l->pz = l->prx * -sin(m->rot.ey) + l->prz * cos(m->rot.ey);
	l->prx = l->px * cos(m->rot.ez) + l->py * -sin(m->rot.ez);
	l->pry = l->px * sin(m->rot.ez) + l->py * cos(m->rot.ez);
	l->prz = l->pz;
}
