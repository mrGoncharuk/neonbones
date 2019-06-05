/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 15:20:54 by mhonchar          #+#    #+#             */
/*   Updated: 2019/03/14 14:49:55 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_rinfo		*ft_create_node(int fd)
{
	t_rinfo	*lst;

	if (!(lst = (t_rinfo *)malloc(sizeof(*lst))))
		return (NULL);
	lst->fd = fd;
	lst->data = ft_strnew(0);
	lst->next = NULL;
	return (lst);
}

t_rinfo		*ft_checkfd(int fd, t_rinfo **head)
{
	t_rinfo	*lst;

	lst = *head;
	if (*head == NULL)
	{
		if (!(lst = ft_create_node(fd)))
			return (NULL);
		*head = lst;
		return (lst);
	}
	while (lst->next)
	{
		if (lst->fd == fd)
			return (lst);
		lst = lst->next;
	}
	if (lst->fd == fd)
		return (lst);
	lst->next = ft_create_node(fd);
	return (lst->next);
}

int			ft_rewrite(char **data, char **line)
{
	char	*part;
	char	*temp;

	if (!(part = ft_strchr(*data, '\n')))
	{
		if (!(temp = ft_strjoin(*line, *data)))
			return (-1);
		ft_strdel(line);
		ft_strdel(data);
		*line = temp;
		return (0);
	}
	part[0] = '\0';
	if (!(temp = ft_strjoin(*line, *data)))
		return (-1);
	ft_strdel(line);
	part = ft_strdup(part + 1);
	ft_strdel(data);
	*data = part;
	*line = temp;
	return (1);
}

int			ft_read_line(t_rinfo **curr_file, char **line)
{
	char	buf[BUFF_SIZE + 1];
	int		r;
	int		inf;

	if ((*curr_file)->data)
		if ((inf = ft_rewrite(&((*curr_file)->data), line)))
			return (inf);
	while ((r = read((*curr_file)->fd, buf, BUFF_SIZE)))
	{
		if (r == -1)
			return (-1);
		buf[r] = '\0';
		(*curr_file)->data = ft_strdup(buf);
		if ((inf = ft_rewrite(&((*curr_file)->data), line)))
			return (inf);
	}
	if ((*curr_file)->data == NULL && ft_strlen(*line) == 0)
		return (0);
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static t_rinfo	*lst = NULL;
	t_rinfo			*curr_file;

	if ((fd < 0) || (BUFF_SIZE < 1) || (read(fd, NULL, 0) == -1) || !line)
		return (-1);
	*line = ft_strnew(0);
	if (!(curr_file = ft_checkfd(fd, &lst)))
		return (-1);
	return (ft_read_line(&curr_file, line));
}
