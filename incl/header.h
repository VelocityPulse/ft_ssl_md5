/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:47:34 by cchameyr          #+#    #+#             */
/*   Updated: 2020/02/06 12:26:28 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HEADER_H
# define FT_HEADER_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdint.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/mman.h>

// update usage (512 / 224)
# define _HASHS_ "[-md5 -sha224 -sha256 -sha384 -sha512]"
# define _USAGE_ "Usage: " _HASHS_ " [-p -q -r -s] [file]\n" 
# define _USAGE_CONTEXT_ "Usage in context: " _HASHS_ " [-p -q -r] [file]\n"

# define BLOCK_BITS 512
# define BLOCK_BYTE 64
# define ALIGN56(SIZE) (((SIZE - 1) + MOD_BYTE) - ((SIZE - 1) % MOD_BYTE))
# define ALIGN64(SIZE) (((SIZE - 1) + BLOCK_BYTE) - ((SIZE - 1) % BLOCK_BYTE))
# define ALIGN128(SIZE) (((SIZE - 1) + 128) - ((SIZE - 1) % 128))

# define SHA2_BLOCK_BYTE 256
# define SHA2_BLOCK_BITS 2048

typedef enum	e_hashflag
{
	T_MD5,
	T_SHA224,
	T_SHA256,
	T_SHA384,
	T_SHA512
}				t_hashflag;

typedef enum	e_origin
{
	STDIN_D,
	STDIN_P,
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
	int			turns;
	t_hashflag	hash;
	void		(*hash_func)();
	t_bool		sslcontext;
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
	uint32_t	s0;
	uint32_t	s1;
	uint32_t	x0;
	uint32_t	x1;
	uint32_t	t1;
	uint32_t	t2;
	uint32_t	ch;
	uint32_t	maj;
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	e;
	uint32_t	f;
	uint32_t	g;
	uint32_t	h;
}				t_sha2;

typedef struct	s_sha512
{
	uint64_t	buff[80];
	uint64_t	state[8];
	int			aligned128;
	uint64_t	s0;
	uint64_t	s1;
	uint64_t	x0;
	uint64_t	x1;
	uint64_t	t1;
	uint64_t	t2;
	uint64_t	ch;
	uint64_t	maj;
	uint64_t	a;
	uint64_t	b;
	uint64_t	c;
	uint64_t	d;
	uint64_t	e;
	uint64_t	f;
	uint64_t	g;
	uint64_t	h;
}				t_sha512;

t_bool			handle_option(int ac, char **av, t_data *ssl);

void			ft_md5(t_content *content, t_data *ssl);
void			ft_sha2(t_content *content, t_data *ssl);
void			ft_sha512(t_content *content, t_data *ssl);

int				block_align(int size, t_hashflag hash);

t_content		*read_file(char *path, t_data *ssl);
t_content		*read_param(char *param, t_data *ssl);
t_content		*read_stdin(t_origin origin, t_data *ssl);
void			parse_help(t_content *content, char *hash, t_data *ssl);




#endif
