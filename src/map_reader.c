/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 13:02:12 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/24 20:02:14 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "neon.h"
#include <stdio.h>

int			ft_get_map_info(int fd, t_game *g)
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
	g->map.width = ft_atoi(map_data[0]);
	g->map.height = ft_atoi(map_data[1]);
	g->player.pos.x = ft_atoi(map_data[2]);
	g->player.pos.y = ft_atoi(map_data[3]);
	ft_free_2darr(map_data);
	if (!(g->map.data = (int **)malloc(g->map.height * sizeof(int *) + 1)))
		return (-1);
	g->map.data[g->map.height] = NULL;
	i = -1;
	while (++i < g->map.height)
		if (!(g->map.data[i] = (int *)malloc(g->map.width * sizeof(int))))
			return (-1);
	return (0);
}

int			ft_get_map_data(t_game *game, t_list *f)
{
	int		i;
	int		j;
	char	**data;

	i = -1;
	while (++i < game->map.height)
	{
		data = ft_strsplit(((char *)f->content), ' ');
		if (ft_len_2darr(data) != game->map.width)
		{
			ft_free_2darr(data);
			return (E_BAD_MAP);
		}
		j = -1;
		while (++j < game->map.width)
		{
			game->map.data[i][j] = ft_atoi(data[j]);
		}
		f = f->next;
		ft_free_2darr(data);
	}
	return (0);
}

int			ft_list_init(t_list **f, t_game *game, int fd)
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
	if (game->map.height != rows)
		return (E_BAD_MAP);
	return (0);
}

int			ft_is_map_valid(t_game *game)
{
	int		j;

	if (game->player.pos.y > game->map.height || game->player.pos.x >
		game->map.width || game->player.pos.y < 0 || game->player.pos.x < 0)
		return (E_BAD_MAP);
	if (game->map.data[(int)(game->player.pos.y) - 1]
		[(int)(game->player.pos.x) - 1] != 0)
		return (E_BAD_MAP);
	j = -1;
	while (++j < game->map.height)
		if (game->map.data[j][0] == 0
			|| game->map.data[j][game->map.width - 1] == 0)
			return (E_BAD_MAP);
	j = -1;
	while (++j < game->map.width)
		if (game->map.data[0][j] == 0
			|| game->map.data[game->map.height - 1][j] == 0)
			return (E_BAD_MAP);
	return (0);
}

int			ft_read_map(t_game *game, const char *fname)
{
	t_list	*f;
	int		fd;
	int		ret;

	if ((ret = ft_file_review(fname)) < 0)
		return (ret);
	fd = open(fname, O_RDONLY);
	if ((ret = ft_get_map_info(fd, game)) < 0)
	{
		close(fd);
		return (ret);
	}
	if ((ret = ft_list_init(&f, game, fd)) < 0)
	{
		ft_del_list(&f);
		return (ret);
	}
	if ((ret = ft_get_map_data(game, f)) < 0)
	{
		ft_del_list(&f);
		return (ret);
	}
	ft_del_list(&f);
	return (ft_is_map_valid(game) + ft_check_map_textures(game));
}
