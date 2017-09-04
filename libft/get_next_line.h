/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 01:48:32 by videsvau          #+#    #+#             */
/*   Updated: 2017/05/20 03:26:17 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H
# define BUFF_SIZE 7000
# include "libft.h"

t_list	*ft_manage_fd(int fd, t_list **chain);
int		get_next_line(const int fd, char **line);
void	join(t_list **alst, char *buff, int end);

#endif
