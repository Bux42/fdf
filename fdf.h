/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 15:25:16 by videsvau          #+#    #+#             */
/*   Updated: 2017/06/01 14:45:33 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H
# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
# include <math.h>

# define WIDTH 1300
# define HEIGHT 1300

typedef struct		s_rot
{
	float			x;
	float			y;
	float			z;
	float			ex;
	float			ey;
	float			ez;
}					t_rot;

typedef struct		s_l
{
	int				px;
	int				py;
	int				pz;
	int				prx;
	int				pry;
	int				prz;
	int				v;
}					t_l;

typedef struct		s_m
{
	void			*ptr;
	void			*win;
	void			*img;
	char			*imga;
	int				height;
	int				width;
	int				sp;
	int				midx;
	int				midy;
	int				midmx;
	int				midmy;
	int				decx;
	int				decy;
	int				rotx;
	int				roty;
	int				rotz;
	int				stp[2];
	int				spx;
	int				spy;
	int				bpp;
	int				colorchange;
	int				colorinterval;
	int				sl;
	int				endian;
	int				color;
	int				scolor;
	int				nbp;
	int				palette;
	int				diff;
	struct s_rot	rot;
	int				maxdiff;
	struct s_l		**l;
}					t_m;

void				parse_file(int fd, t_m *mlx, t_l ***line);
int					mouse_hook(int button, int x, int y, t_m *mlx);
int					key_hook(int keycode, t_m *m);
int					expose_hook(t_m *m);

void				put_pixel(t_m *mlx, int x, int y, int color);
void				draw_line(t_l line1, t_l line2, t_m *mlx);
void				value(t_l line1, t_l line2, int values[6]);
int					nbpx(int x0, int y0, int x1, int y1);
void				degree_to_rad(t_rot *rot);
void				draw_right(t_m *m, t_l line, t_l line2);
void				draw_down(t_m *m, t_l line, t_l line2);

void				rotation(t_l *line, t_m *mlx);
void				center_grid(t_m **mlxx);
void				prepare_grid(t_m **mlxx);

void				move(int keycode, t_m *mlx);
void				rotate(int keycode, t_m *mlx);
void				zoom(int keycode, t_m *mlx);
void				color(int keycode, t_m *mlx);

void				init_window(t_m *m);
int					visualize(t_m *mlx, int fd, char *argv);
void				draw_grid(t_m **mlx);
void				clear_image(t_m *mlx);
int					min_value(t_m *mlx);
void				normalize(t_m *mlx);

t_l					**struct_alloc(int height, int width);
void				free_struct(t_l **line, int height);
void				exiting(t_m *mlx);

int					max_diff(t_m *mlx);
void				scale_down(t_m *mlx, t_l ***line);

int					nb_elem(char *str);
int					valid(char c);
int					validcolor(char *str, int i);
int					syntax_error(char *str);
int					check_syntax(int fd, t_m *mlx);
int					next_nb(int i, char *str, int j);

#endif
