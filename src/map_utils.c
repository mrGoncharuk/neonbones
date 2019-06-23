/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 15:46:43 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/23 18:39:39 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "neon.h"

int		ft_len_2darr(char **arr)
{
	int		i;

	if (arr == NULL)
		return (-1);
	i = 0;
	while (*(arr + i))
		i++;
	return (i);
}

void	ft_free_2darr(char **arr)
{
	int		i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr[i]);
}

void	ft_del_list(t_list **lst)
{
	t_list	*f;
	t_list	*next;

	if (lst == NULL)
		return ;
	f = *lst;
	while (f)
	{
		next = f->next;
		free(f->content);
		free(f);
		f = next;
	}
}

int			ft_file_review(const char *fname)
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
