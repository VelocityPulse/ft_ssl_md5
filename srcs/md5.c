/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:47:34 by cchameyr          #+#    #+#             */
/*   Updated: 2020/03/03 10:15:58 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/header.h"

static const uint32_t	g_s_md5[64] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, \
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, \
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, \
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

static const uint32_t	g_k_md5[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, \
	0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, \
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340, \
	0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8, \
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, \
	0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, \
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa, \
	0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, \
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, \
	0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, \
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

static void				ft_md5_init_padding(char *s, int len, t_md5 *md5)
{
	md5->state[0] = 0x67452301;
	md5->state[1] = 0xefcdab89;
	md5->state[2] = 0x98badcfe;
	md5->state[3] = 0x10325476;
	md5->aligned64 = block_align(len, T_MD5);
	ft_bzero(md5->buff, 64);
	s[len] = -128;
	((uint64_t *)s)[md5->aligned64 / 8 - 1] = len * 8;
}

static void				ft_md5_processing(t_md5 *md5, int i)
{
	if (i < 16)
	{
		md5->f = (md5->b & md5->c) | ((~md5->b) & md5->d);
		md5->g = i;
	}
	else if (i < 32)
	{
		md5->f = (md5->d & md5->b) | ((~md5->d) & md5->c);
		md5->g = (5 * i + 1) % 16;
	}
	else if (i < 48)
	{
		md5->f = md5->b ^ md5->c ^ md5->d;
		md5->g = (3 * i + 5) % 16;
	}
	else
	{
		md5->f = md5->c ^ (md5->b | (~md5->d));
		md5->g = (7 * i) % 16;
	}
	md5->f = md5->f + md5->a + g_k_md5[i] + md5->buff[md5->g];
	md5->a = md5->d;
	md5->d = md5->c;
	md5->c = md5->b;
	md5->b = md5->b + ft_b32rotate_left(md5->f, g_s_md5[i]);
}

static void				ft_md5_loop(char *str, t_md5 *md5)
{
	int		rest;
	int		block;
	int		i;

	block = 0;
	rest = md5->aligned64 * 8;
	while (rest > 0)
	{
		rest -= BLOCK_BITS;
		ft_memcpy((void *)md5->buff, str + (64 * block++), 64);
		ft_memcpy(&md5->a, md5->state, 4 * 4);
		i = -1;
		while (++i < 64)
			ft_md5_processing(md5, i);
		md5->state[0] += md5->a;
		md5->state[1] += md5->b;
		md5->state[2] += md5->c;
		md5->state[3] += md5->d;
	}
}

void					ft_md5(t_content *content, t_data *ssl)
{
	t_md5	md5;
	char	digest[16];
	int		i;

	ft_bzero(digest, 16);
	ft_md5_init_padding(content->content, content->size, &md5);
	ft_md5_loop(content->content, &md5);
	if (content->origin == STDIN_P)
		ft_printf("%s\n", content->name);
	else if (!ssl->q_flag && !ssl->r_flag)
		parse_help(content, "MD5", ssl);
	ft_memcpy(digest, md5.state, 16);
	i = -1;
	while (++i < 16)
		ft_printf("%02x", digest[i] & 0xFF);
	if (!ssl->q_flag && ssl->r_flag)
		parse_help(content, "MD5", ssl);
	else
		ft_putchar('\n');
}
