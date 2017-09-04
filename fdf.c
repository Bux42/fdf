/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 15:25:17 by videsvau          #+#    #+#             */
/*   Updated: 2017/05/29 03:21:58 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		key_hook(int keycode, t_m *m)
{
	if (keycode == 53)
		exiting(m);
	if (keycode == 92)
	{
		m->spx -= 10;
		m->spy += 10;
	}
	if (keycode == 91)
		m->spy += 10;
	if (keycode == 89)
	{
		m->spx += 10;
		m->spy += 10;
	}
	if (keycode > 82 && keycode < 91)
		move(keycode, m);
	if (keycode < 15 && keycode > -1)
		rotate(keycode, m);
	if (keycode == 78 || keycode == 69)
		zoom(keycode, m);
	if (keycode > 16 && keycode < 28)
		color(keycode, m);
	draw_grid(&m);
	return (0);
}

int		mouse_hook(int button, int x, int y, t_m *m)
{
	x++;
	y++;
	y--;
	x--;
	if (button == 7)
		m->rot.x += 1;
	if (button == 6)
		m->rot.x -= 1;
	if (button == 5)
		m->rot.y += 1;
	if (button == 4)
		m->rot.y -= 1;
	draw_grid(&m);
	mlx_put_image_to_window(m->ptr, m->win, m->img, 0, 0);
	return (0);
}

int		expose_hook(t_m *m)
{
	m->midx = HEIGHT / 2;
	m->midy = WIDTH / 2;
	m->midmx = m->height / 2;
	m->midmy = m->width / 2;
	m->colorinterval = 1;
	m->colorchange = 1;
	draw_grid(&m);
	return (0);
}

void	init_window(t_m *m)
{
	m->scolor = 0x50ee00;
	m->color = 0x50ee00;
	m->spx = 0;
	m->spy = 0;
	m->rot.x = 180;
	m->rot.y = 0;
	m->rot.z = 90;
	m->sp = (WIDTH / m->width) / 1.2;
	if ((m->ptr = mlx_init()) == NULL)
		ft_putendl("Failed to create mlx ptr");
	m->img = mlx_new_image(m->ptr, WIDTH, HEIGHT);
	m->imga = mlx_get_data_addr(m->img, &(m->bpp), &(m->sl), &(m->endian));
	m->win = mlx_new_window(m->ptr, WIDTH, HEIGHT, "fdf");
	mlx_key_hook(m->win, key_hook, m);
	mlx_mouse_hook(m->win, mouse_hook, m);
	mlx_expose_hook(m->win, expose_hook, m);
	mlx_loop(m->ptr);
}

int		main(int ac, char **av)
{
	int		fd;
	t_m		mlx;

	if (ac == 2)
	{
		mlx.height = 0;
		mlx.width = 0;
		if ((fd = open(av[1], O_RDONLY)) == -1)
			return (0);
		if (check_syntax(fd, &mlx) == 1)
			if (visualize(&mlx, fd, av[1]))
				free_struct(mlx.l, mlx.height);
	}
	return (0);
}
