/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 07:15:20 by videsvau          #+#    #+#             */
/*   Updated: 2017/05/22 16:57:29 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_l		**struct_alloc(int height, int width)
{
	t_l		**line;
	int		i;

	line = NULL;
	i = 0;
	if (!(line = (t_l**)malloc(sizeof(t_l*) * height)))
		return (line);
	while (i < height)
	{
		if (!(line[i] = (t_l*)malloc(sizeof(t_l) * width)))
			return (line);
		i++;
	}
	return (line);
}

void	free_struct(t_l **line, int height)
{
	int		i;

	i = 0;
	while (i < height)
	{
		free(line[i]);
		i++;
	}
	free(line);
}

void	exiting(t_m *mlx)
{
	mlx_destroy_image(mlx->ptr, mlx->img);
	mlx_destroy_window(mlx->ptr, mlx->win);
	free_struct(mlx->l, mlx->height);
	exit(0);
}

int		min_value(t_m *mlx)
{
	int		min;
	int		x;
	int		y;

	min = 2147483647;
	x = 0;
	while (x < mlx->height)
	{
		y = 0;
		while (y < mlx->width)
		{
			if (min > mlx->l[x][y].v)
				min = mlx->l[x][y].v;
			y++;
		}
		x++;
	}
	return (min);
}

void	normalize(t_m *mlx)
{
	int		x;
	int		y;
	int		inc;
	int		min;

	x = 0;
	inc = 0;
	min = min_value(mlx);
	if (min < 1)
		inc = abs(min) + 1;
	else if (min > 1)
		inc = -min + 1;
	while (x < mlx->height)
	{
		y = 0;
		while (y < mlx->width)
		{
			mlx->l[x][y].v += inc;
			y++;
		}
		x++;
	}
}
