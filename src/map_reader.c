/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 13:02:12 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/07 20:16:27 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "neon.h"

int			ft_file_review(char *fname)
{
	int		fd;
	char	buf[1];

	if (!(fd = open(fname, O_RDONLY)) || fd < 0 || (read(fd, NULL, 0) == -1))
		return (E_NOFILE);
	if (read(fd, buf, 1) == 0)
		return (E_EMPTY_FILE);
	close(fd);
	return (0);
}

int			ft_get_map_info(int fd, t_game *win)
{
	char	*line;
	char	**map_data;
	int		i;

	get_next_line(fd, &line);
	map_data = ft_strsplit(line, ' ');
	free(line);
	if (ft_len_2darr(map_data) != 4)
	{
		ft_free_2darr(map_data);
		return (E_BAD_MAP);
	}
	win->map.width = ft_atoi(map_data[0]);
	win->map.height = ft_atoi(map_data[1]);
	win->player.pos.x = ft_atoi(map_data[2]);
	win->player.pos.y = ft_atoi(map_data[3]);
	ft_free_2darr(map_data);
	if (!(win->map.data = (int **)malloc(win->map.height * sizeof(int *) + 1)))
		return (-1);
	win->map.data[win->map.height] = NULL;
	i = -1;
	while (++i < win->map.height)
		if (!(win->map.data[i] = (int *)malloc(win->map.width * sizeof(int))))
			return (-1);
	return (0);
}

int			ft_get_map_data(t_game *win, t_list *f)
{
	int		i;
	int		j;
	char	**data;

	i = -1;
	while (++i < win->map.height)
	{
		data = ft_strsplit(((char *)f->content), ' ');
		if (ft_len_2darr(data) != win->map.width)
		{
			ft_free_2darr(data);
			return (E_BAD_MAP);
		}
		j = -1;
		while (++j < win->map.width)
		{
			win->map.data[i][j] = ft_atoi(data[j]);
		}
		f = f->next;
		ft_free_2darr(data);
	}
	return (0);
}

int			ft_list_init(t_list **f, t_game *win, int fd)
{
	t_list	*next;
	int		rows;

	(*f) = ft_lstnew(NULL, 0);
	next = (*f);
	while (get_next_line(fd, (char **)&(next->content)))
	{
		next->next = ft_lstnew(NULL, 0);
		next = next->next;
	}
	close(fd);
	next = (*f);
	rows = 0;
	while (next->next != NULL)
	{
		next = next->next;
		rows++;
	}
	if (win->map.height != rows)
		return (E_BAD_MAP);
	return (0);
}

int		ft_is_map_valid(t_game *win)
{
	int		j;

	if (win->player.pos.y > win->map.height || win->player.pos.x > win->map.width ||
		win->player.pos.y < 0 || win->player.pos.x < 0)
		return (E_BAD_MAP);
	if (win->map.data[(int)(win->player.pos.y) - 1][(int)(win->player.pos.x) - 1] != 0)
		return (E_BAD_MAP);
	j = -1;
	while (++j < win->map.height)
		if (win->map.data[j][0] == 0
			|| win->map.data[j][win->map.width - 1] == 0)
			return (E_BAD_MAP);
	j = -1;
	while (++j < win->map.width)
		if (win->map.data[0][j] == 0
			|| win->map.data[win->map.height - 1][j] == 0)
			return (E_BAD_MAP);
	win->player.pos.y = win->player.pos.y * WB_SIZE + 32;
	win->player.pos.x = win->player.pos.x * WB_SIZE + 32;
	return (0);
}

int			ft_read_map(t_game *win, char *fname)
{
	t_list	*f;
	int		fd;
	int		ret;

	if ((ret = ft_file_review(fname)) < 0)
		return (ret);
	fd = open(fname, O_RDONLY);
	if ((ret = ft_get_map_info(fd, win)) < 0)
	{
		close(fd);
		return (ret);
	}
	if ((ret = ft_list_init(&f, win, fd)) < 0)
	{
		ft_del_list(&f);
		return (ret);
	}
	if ((ret = ft_get_map_data(win, f)) < 0)
	{
		ft_del_list(&f);
		return (ret);
	}
	ft_del_list(&f);
	return (ft_is_map_valid(win));
}
