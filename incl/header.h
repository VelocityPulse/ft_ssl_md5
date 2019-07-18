/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:47:34 by cchameyr          #+#    #+#             */
/*   Updated: 2019/07/18 19:06:40 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HEADER_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdint.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>

# define _USAGE_ "Usage: [-md5 -sha256] [-p -q -r -s] [file]\n"

# define MOD_BITS 448
# define MOD_BYTE 56
# define LENGHT_ALIGN(SIZE) (((SIZE) + MOD_BYTE) - ((SIZE) % MOD_BYTE))

typedef enum	e_hashflag
{
	T_MD5,
	T_SHA256,
	NB_TYPE,
}				t_hashflag;

typedef struct	s_data
{
	t_hashflag	hash_flag;
	t_bool		p_flag;
	t_bool		q_flag;
	t_bool		r_flag;
	t_bool		s_flag;
	t_lststr	*files_name;
	t_list		*files_content;
}				t_data;

typedef struct	s_md5
{
	uint32_t	buff[16]; // block 512
	uint32_t	state[4]; // abcd 128
	int			count;
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
}				t_md5;

void		ft_md5_handle(t_data *ssl_data, char *str, int len);

void		get_content(t_data *ssl_data);

#endif
