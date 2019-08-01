/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:47:34 by cchameyr          #+#    #+#             */
/*   Updated: 2019/08/01 13:25:56 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/header.h"

static const uint32_t	g_k_sha2[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, \
	0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, \
	0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, \
	0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, \
	0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, \
	0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, \
	0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, \
	0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, \
	0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, \
	0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, \
	0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

static void				ft_sha2_init_padding(char *s, int len, t_sha2 *sha2)
{
	int		i;
	int		lenght32;

	sha2->state[0] = 0x6a09e667;
	sha2->state[1] = 0xbb67ae85;
	sha2->state[2] = 0x3c6ef372;
	sha2->state[3] = 0xa54ff53a;
	sha2->state[4] = 0x510e527f;
	sha2->state[5] = 0x9b05688c;
	sha2->state[6] = 0x1f83d9ab;
	sha2->state[7] = 0x5be0cd19;
	sha2->aligned64 = block_align64(len);
	ft_bzero(sha2->buff, 64 * 4);
	s[len] = -128;
	lenght32 = sha2->aligned64 / 4;
	i = -1;
	while (++i < lenght32)
		((uint32_t *)s)[i] = ft_bswap32(((uint32_t *)s)[i]);
	((uint32_t *)s)[sha2->aligned64 / 4 - 1] = len * 8;
}

static void				ft_sha2_core_message(uint32_t *buff, char *str,
		int *block, t_sha2 *sha2)
{
	int		i;

	ft_memcpy((void *)buff, str + (64 * (*block)++), 64);
	i = 15;
	while (++i < 64)
	{
		sha2->s0 = ft_b32rotate_right(buff[i - 15], 7) ^
			ft_b32rotate_right(buff[i - 15], 18) ^ (buff[i - 15] >> 3);
		sha2->s1 = ft_b32rotate_right(buff[i - 2], 17) ^
			ft_b32rotate_right(buff[i - 2], 19) ^ (buff[i - 2] >> 10);
		buff[i] = buff[i - 16] + sha2->s0 + buff[i - 7] + sha2->s1;
	}
	ft_memcpy(&sha2->a, sha2->state, 8 * 4);
}

static void				ft_sha2_core(t_sha2 *s)
{
	int		i;

	i = -1;
	while (++i < 64)
	{
		s->x1 = ft_b32rotate_right(s->e, 6) ^
			ft_b32rotate_right(s->e, 11) ^ ft_b32rotate_right(s->e, 25);
		s->ch = (s->e & s->f) ^ ((~s->e) & s->g);
		s->t1 = s->h + s->x1 + s->ch + g_k_sha2[i] + s->buff[i];
		s->x0 = ft_b32rotate_right(s->a, 2) ^
			ft_b32rotate_right(s->a, 13) ^ ft_b32rotate_right(s->a, 22);
		s->maj = (s->a & s->b) ^ (s->a & s->c) ^ (s->b & s->c);
		s->t2 = s->x0 + s->maj;
		s->h = s->g;
		s->g = s->f;
		s->f = s->e;
		s->e = s->d + s->t1;
		s->d = s->c;
		s->c = s->b;
		s->b = s->a;
		s->a = s->t1 + s->t2;
	}
}

static void				ft_sha2_loop(char *str, t_sha2 *sha2)
{
	int		rest;
	int		block;

	rest = sha2->aligned64 * 8;
	block = 0;
	while (rest > 0)
	{
		rest -= BLOCK_BITS;
		ft_sha2_core_message(sha2->buff, str, &block, sha2);
		ft_sha2_core(sha2);
		sha2->state[0] += sha2->a;
		sha2->state[1] += sha2->b;
		sha2->state[2] += sha2->c;
		sha2->state[3] += sha2->d;
		sha2->state[4] += sha2->e;
		sha2->state[5] += sha2->f;
		sha2->state[6] += sha2->g;
		sha2->state[7] += sha2->h;
	}
}

void					ft_sha2(t_content *content, t_data *ssl)
{
	t_sha2	sha2;
	int		i;
	char	digest[32];

	ft_bzero(digest, 32);
	ft_sha2_init_padding(content->content, content->size, &sha2);
	ft_sha2_loop(content->content, &sha2);
	if (content->origin == STDIN_P)
		ft_printf("%s\n", content->name);
	else if (!ssl->q_flag && !ssl->r_flag)
		parse_help(content, "SHA256", ssl);
	i = -1;
	while (++i < 8)
		sha2.state[i] = ft_bswap32(sha2.state[i]);
	ft_memcpy(digest, sha2.state, 32);
	i = -1;
	while (++i < 32)
		ft_printf("%02x", digest[i] & 0xFF);
	if (!ssl->q_flag && ssl->r_flag)
		parse_help(content, "SHA256", ssl);
	else
		ft_putchar('\n');
}
