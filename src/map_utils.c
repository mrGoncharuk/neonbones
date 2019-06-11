/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 15:46:43 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/06 16:01:38 by mhonchar         ###   ########.fr       */
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
		return;
	f = *lst;
	while (f)
	{
		next = f->next;
		free(f->content);
		free(f);
		f = next;
	}
}
