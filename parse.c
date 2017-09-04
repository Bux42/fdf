/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 12:56:42 by videsvau          #+#    #+#             */
/*   Updated: 2017/06/01 15:41:41 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		scale_down(t_m *mlx, t_l ***lined)
{
	t_l		**line;
	int		x;
	int		y;

	line = *lined;
	x = 0;
	while (x < mlx->height)
	{
		y = -1;
		while (++y < mlx->width)
		{
			if (line[x][y].v > 255)
				line[x][y].v = 255;
		}
		x++;
	}
}

int			visualize(t_m *mlx, int fd, char *argv)
{
	if ((mlx->height + mlx->width) < 3)
		return (0);
	mlx->l = struct_alloc(mlx->height, mlx->width);
	close(fd);
	if ((fd = open(argv, O_RDONLY)) == -1)
		return (0);
	parse_file(fd, mlx, &mlx->l);
	close(fd);
	mlx->maxdiff = max_diff(mlx);
	normalize(mlx);
	if (mlx->maxdiff > 255)
	{
		mlx->maxdiff = 255;
		scale_down(mlx, &mlx->l);
	}
	if (mlx->maxdiff < 0)
		return (0);
	init_window(mlx);
	return (0);
}

int			next_nb(int i, char *str, int j)
{
	int	ret;

	ret = 2;
	while (str[++j] == ' ' || str[j] == '\n' || str[j] == '\t')
		ret++;
	if (i < 0)
	{
		ret++;
		j++;
		i = -i;
	}
	while (i > 9)
	{
		i /= 10;
		j++;
		ret++;
	}
	if (str[j + 1] == ',')
	{
		j += 11;
		ret += 9;
	}
	return (ret);
}

void		parse_file(int fd, t_m *mlx, t_l ***lined)
{
	char	*str;
	t_l		**line;
	int		xyi[3];

	xyi[0] = 0;
	line = *lined;
	while (get_next_line(fd, &str) && xyi[0] < mlx->height)
	{
		xyi[1] = 0;
		xyi[2] = 0;
		while (xyi[2] < (int)ft_strlen(str))
		{
			line[xyi[0]][xyi[1]].v = ft_atoi(&(str)[xyi[2]]);
			line[xyi[0]][xyi[1]].px = xyi[0];
			line[xyi[0]][xyi[1]].py = xyi[1];
			xyi[1]++;
			xyi[2] += next_nb(ft_atoi(&(str)[xyi[2]]), str, xyi[2] - 1);
		}
		xyi[0]++;
		free(str);
	}
}
