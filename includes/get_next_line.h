/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:20:33 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/19 14:13:44 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

//# define _CRT_SECURE_NO_WARNINGS
# include <fcntl.h>
// # include <io.h>
# include <sys/types.h>
# include <sys/uio.h>
# include "libft.h"
# define BUFF_SIZE 15
// # define read _read
// # define open _open
// # define close _close


int					get_next_line(const int fd, char **line);

typedef struct		s_rinfo
{
	int				fd;
	char			*data;
	struct s_rinfo	*next;
}					t_rinfo;

#endif
