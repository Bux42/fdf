/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 14:08:40 by videsvau          #+#    #+#             */
/*   Updated: 2017/05/25 18:30:18 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		nb_elem(char *str)
{
	int		i;
	int		nb1;

	i = 0;
	nb1 = 0;
	while (str[i])
	{
		if (str[i] == '\t' || str[i] == ' ' || str[i] == '\n')
		{
			while (str[i] && (str[i] == '\t' || str[i] == ' ' ||
						str[i] == '\n'))
				i++;
		}
		if (str[i] == '-' || (str[i] > 47 && str[i] < 58))
		{
			while ((str[i] > 47 && str[i] < 58 && str[i]) || str[i] == '-')
				i++;
			if (str[i] == ',')
				i += 9;
			nb1++;
		}
	}
	return (nb1);
}

int		valid(char c)
{
	if (c < 58 && c > 47)
		return (1);
	if (c == ' ' || c == '\n' || c == '-' || c == '\t' || c == '\0')
		return (1);
	return (0);
}

int		validcolor(char *str, int i)
{
	if (!valid(str[i + 9]))
		return (0);
	return (1);
}

int		syntax_error(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == ',')
		{
			if (!validcolor(str, i))
				return (1);
			i += 9;
		}
		if (str[i] == '\0')
			return (0);
		if (!valid(str[i]))
			return (1);
	}
	return (0);
}

int		check_syntax(int fd, t_m *m)
{
	char	*str;
	int		cmp[2];

	while (get_next_line(fd, &str))
	{
		if ((!str) || (syntax_error(str)) || ft_strlen(str) == 0)
			return (0);
		m->width = nb_elem(str);
		if (m->height % 2 == 0)
		{
			cmp[0] = m->width;
			if (m->height > 0)
				if (cmp[0] != cmp[1])
					return (0);
		}
		else
		{
			cmp[1] = m->width;
			if (cmp[1] != cmp[0])
				return (0);
		}
		m->height++;
		ft_strdel(&str);
	}
	return (1);
}
