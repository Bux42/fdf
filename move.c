/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 15:25:17 by videsvau          #+#    #+#             */
/*   Updated: 2017/05/22 16:57:23 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		color(int keycode, t_m *mlx)
{
	if (keycode == 20)
		mlx->scolor = 0x00ff00;
	if (keycode == 18)
		mlx->scolor = 0x50ee00;
	if (keycode == 19)
		mlx->scolor = 0xee3c00;
	if (keycode == 21)
		mlx->scolor = 0xeeee00;
	if (keycode == 23)
		mlx->scolor = 0xffff00;
}

void		move(int keycode, t_m *mlx)
{
	if (keycode == 87)
	{
		mlx->rot.x = 180;
		mlx->rot.y = 0;
		mlx->rot.z = 90;
		mlx->spx = 0;
		mlx->spy = 0;
		mlx->sp = (WIDTH / mlx->width) / 1.2;
	}
	if (keycode == 86)
		mlx->spx += 10;
	if (keycode == 88)
		mlx->spx -= 10;
	if (keycode == 84)
		mlx->spy -= 10;
	if (keycode == 85)
	{
		mlx->spx -= 10;
		mlx->spy -= 10;
	}
	if (keycode == 83)
	{
		mlx->spx += 10;
		mlx->spy -= 10;
	}
}

void		zoom(int keycode, t_m *mlx)
{
	if (keycode == 78 && mlx->sp > 1)
		mlx->sp -= 1;
	if (keycode == 69)
		mlx->sp += 1;
}
