/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:20:33 by mhonchar          #+#    #+#             */
/*   Updated: 2019/02/24 14:58:06 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include "libft.h"
# define BUFF_SIZE 15

int					get_next_line(const int fd, char **line);

typedef struct		s_rinfo
{
	int				fd;
	char			*data;
	struct s_rinfo	*next;
}					t_rinfo;

#endif
