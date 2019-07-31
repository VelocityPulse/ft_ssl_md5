/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:47:34 by cchameyr          #+#    #+#             */
/*   Updated: 2019/07/31 19:44:49 by cchameyr         ###   ########.fr       */
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
# define BLOCK_BITS 512
# define BLOCK_BYTE 64
# define ALIGN56(SIZE) (((SIZE - 1) + MOD_BYTE) - ((SIZE - 1) % MOD_BYTE))
# define ALIGN64(SIZE) (((SIZE - 1) + BLOCK_BYTE) - ((SIZE - 1) % BLOCK_BYTE))

# define SHA2_BLOCK_BYTE 256
# define SHA2_BLOCK_BITS 2048

typedef enum	e_hashflag
{
	T_MD5,
	T_SHA256,
	NB_TYPE,
}				t_hashflag;

typedef enum	e_origin
{
	STDIN,
	PARAM,
	FILE
}				t_origin;

typedef struct	s_content
{
	void		*content;
	int			size;
	char		*name;
	t_origin	origin;
}				t_content;

typedef struct	s_data
{
	t_hashflag	hash_flag;
	t_bool		q_flag;
	t_bool		r_flag;
}				t_data;

typedef struct	s_md5
{
	uint32_t	buff[16];
	uint32_t	state[4];
	int			aligned64;
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	f;
	uint32_t	g;
}				t_md5;

typedef struct	s_sha2
{
	uint32_t	buff[64];
	uint32_t	state[8];
	int			aligned64;
	int			s0;
	int			s1;
	int			x0;
	int			x1;
	int			t1;
	int			t2;
	int			ch;
	int			maj;
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	e;
	uint32_t	f;
	uint32_t	g;
	uint32_t	h;
}				t_sha2;

void		ft_md5(t_content *content, t_data *ssl);
void		ft_sha2(t_content *content, t_data *ssl);

int			block_align64(int size);

t_content	*read_file(char *path);
t_content	*read_param(char *param);
t_content	*read_stdin(void);

#endif
