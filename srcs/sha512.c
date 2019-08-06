/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:47:34 by cchameyr          #+#    #+#             */
/*   Updated: 2019/08/06 23:39:07 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/header.h"

static const uint64_t g_k_sha512[80] = {
	0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f,
	0xe9b5dba58189dbbc, 0x3956c25bf348b538, 0x59f111f1b605d019,
	0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242,
	0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
	0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235,
	0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
	0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65, 0x2de92c6f592b0275,
	0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
	0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f,
	0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725,
	0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc,
	0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
	0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6,
	0x92722c851482353b, 0xa2bfe8a14cf10364, 0xa81a664bbc423001,
	0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218,
	0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
	0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99,
	0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
	0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc,
	0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
	0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915,
	0xc67178f2e372532b, 0xca273eceea26619c, 0xd186b8c721c0c207,
	0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba,
	0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
	0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc,
	0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
	0x5fcb6fab3ad6faec, 0x6c44198c4a475817
};

static const uint64_t	g_state_sha512[8] = {
	0x6a09e667f3bcc908, 0xbb67ae8584caa73b, 0x3c6ef372fe94f82b,
	0xa54ff53a5f1d36f1, 0x510e527fade682d1, 0x9b05688c2b3e6c1f,
	0x1f83d9abfb41bd6b, 0x5be0cd19137e2179
};

static void				ft_sha512_init_padding(char *s, int len, t_sha512 *sha512)
{
	int		i;
	int		lenght32;

	ft_memcpy(sha512->state, g_state_sha512, 8 * 4);
	sha512->aligned64 = block_align64(len);
	ft_bzero(sha512->buff, 64 * 4);
	s[len] = -128;
	lenght32 = sha512->aligned64 / 4;
	i = -1;
	while (++i < lenght32)
		((uint32_t *)s)[i] = ft_bswap32(((uint32_t *)s)[i]);
	((uint32_t *)s)[sha512->aligned64 / 4 - 1] = len * 8;
}

static void				ft_sha512_core_message(uint64_t *buff, char *str,
		int *block, t_sha512 *sha512)
{
	int		i;

	ft_printf("jump : %d\n", (128 * (*block)));
	ft_memcpy((void *)buff, str + (128 * (*block)++), 128);
	i = 15;
	while (++i < 80)
	{
		sha512->s0 = ft_b64rotate_right(buff[i - 15], 7) ^
			ft_b64rotate_right(buff[i - 15], 18) ^ (buff[i - 15] >> 3);
		sha512->s1 = ft_b64rotate_right(buff[i - 2], 17) ^
			ft_b64rotate_right(buff[i - 2], 19) ^ (buff[i - 2] >> 10);
		buff[i] = buff[i - 16] + sha512->s0 + buff[i - 7] + sha512->s1;
	}
	ft_memcpy(&sha512->a, sha512->state, 8 * 8);
}

static void				ft_sha512_core(t_sha512 *s)
{
	int		i;

	i = -1;
	while (++i < 80)
	{
		s->x1 = ft_b64rotate_right(s->e, 6) ^
			ft_b64rotate_right(s->e, 11) ^ ft_b64rotate_right(s->e, 25);
		s->ch = (s->e & s->f) ^ ((~s->e) & s->g);
		s->t1 = s->h + s->x1 + s->ch + g_k_sha512[i] + s->buff[i];
		s->x0 = ft_b64rotate_right(s->a, 2) ^
			ft_b64rotate_right(s->a, 13) ^ ft_b64rotate_right(s->a, 22);
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

static void				ft_sha512_loop(char *str, t_sha512 *sha512)
{
	int		rest;
	int		block;

	rest = sha512->aligned64 * 8;
	block = 0;
	while (rest > 0)
	{
		rest -= 1024;
		ft_sha512_core_message(sha512->buff, str, &block, sha512);
		ft_sha512_core(sha512);
		sha512->state[0] += sha512->a;
		sha512->state[1] += sha512->b;
		sha512->state[2] += sha512->c;
		sha512->state[3] += sha512->d;
		sha512->state[4] += sha512->e;
		sha512->state[5] += sha512->f;
		sha512->state[6] += sha512->g;
		sha512->state[7] += sha512->h;
	}
}

void					ft_sha512(t_content *content, t_data *ssl)
{
	t_sha512	sha512;
	int		i;
	// int		digest_lenght;
	char	digest[64];

	ft_bzero(digest, 64);
	ft_sha512_init_padding(content->content, content->size, &sha512);
	ft_sha512_loop(content->content, &sha512);
	if (content->origin == STDIN_P)
		ft_printf("%s\n", content->name);
	else if (!ssl->q_flag && !ssl->r_flag)
		parse_help(content, "SHA512", ssl);
	i = -1;
	while (++i < 8)
		sha512.state[i] = ft_bswap64(sha512.state[i]);
	ft_memcpy(digest, sha512.state, 64);
	// digest_lenght = ssl->hash == t_sha51256 ? 32 : 28;
	i = -1;
	while (++i < 64)
		ft_printf("%02x", digest[i] & 0xFF);
	if (!ssl->q_flag && ssl->r_flag)
		parse_help(content, "SHA512", ssl);
	else
		ft_putchar('\n');
}
