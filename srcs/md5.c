/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:47:34 by cchameyr          #+#    #+#             */
/*   Updated: 2019/07/22 14:51:49 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/header.h"

void bitscounter_uint32(int len)
{
	ft_printf("bytes for %d int32 = %d soit %dbits\n", len, sizeof(uint32_t) * len, sizeof(uint32_t) * len * 8);
}

void bitscounter_char(char *str)
{
	ft_printf("bytes for string str = %d soit %dbits\n", sizeof(char) * ft_strlen(str), sizeof(char) * ft_strlen(str) * 8);
}

void unitest_putmem(void const *p, int len)
{
	int i = 0;
	unsigned char *t;

	t = (unsigned char *)p;
	i = 0;
	while (i++ < len)
		ft_printf(" %.2x", t[i]);
	ft_printf("\n");
}

void printBits(void const * const ptr, size_t size)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i = 0; i < size; i++)
    {
		if (i != 0)
			ft_printf(" ");
		if (!(i % 8) && i != 0)
			ft_printf("\n");
		ft_printf("[%03d]", i);
        for (j = 7; j >= 0; j--)
        {
            byte = (b[i] >> j) & 1;
            ft_printf("%u", byte);
        }
    }
    ft_printf("\n\n");
}

static const uint32_t	g_r[64] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, \
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, \
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, \
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

static const uint32_t	g_k[64] = {
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

#include <stdio.h>

void		ft_md5_handle(t_data *ssl_data, char *str, int len)
{
	t_md5	md5;

	md5.state[0] = 0x67452301;
	md5.state[1] = 0xefcdab89;
	md5.state[2] = 0x98badcfe;
	md5.state[3] = 0x10325476;
	md5.count = 0;
	md5.aligned56 = ALIGN56(len);
	md5.aligned64 = ALIGN64(md5.aligned56);

	ft_bzero(md5.buff, 64);
	ft_printf("len : %d\n", len);
	ft_printf("bits : %d\n", len * 8);
	ft_printf("aligned56: %d\n", md5.aligned56);

	// debug
	int t = md5.aligned56 / 4 - 1;
	ft_printf("t = %d\n\n", t * 4);

	// setting padding
	str[len] = -128;

	//big endian
	//((uint64_t *)str)[md5.aligned64 / 8 - 1] = ft_bswap64(len * 8);

	//little endian
	((uint64_t *)str)[md5.aligned64 / 8 - 1] = len * 8;

	// bits debug :
	// ft_printf("print str:\n");
	// printBits(str, len);
	// ft_printf("print str aligned:\n");
	// printBits(str, md5.aligned64);

	// processing blocks
	int rest = md5.aligned64 * 8;
	int block = 0;
	while (rest > 0)
	{
		ft_printf("\n");
		ft_printf("rest : %d\n", rest);
		ft_memcpy((void *)md5.buff, str + (64 * block++), 64);
		rest -= 512;

		// debug print
		for (int i = 0; i < 16; i++)
		{
			// big endian
			// ft_printf("[%d]\t: %ld\n", i, ft_bswap32(md5.buff[i]));

			//little endian
			ft_printf("[%d]\t: %ld\n", i, md5.buff[i]);
		}


		// ALGO
		md5.a = md5.state[0];
		md5.b = md5.state[1];
		md5.c = md5.state[2];
		md5.d = md5.state[3];

		int i = -1;

		while (++i < 64)
		{
			if (i < 16)
			{
				md5.f = (md5.b & md5.c) | ((~md5.b) & md5.d);
				md5.g = i;
			}
			else if (i < 32)
			{
				md5.f = (md5.d & md5.b) | ((~md5.d) & md5.c);
				md5.g = (5 * i + 1) % 16;
			}
			else if (i < 48)
			{
				md5.f = md5.b ^ md5.c ^ md5.d;
				md5.g = (3 * i + 5) % 16;
			}
			else
			{
				md5.f = md5.c ^ (md5.b | (~md5.d));
				md5.g = (7 * i) % 16;
			}

			md5.f = md5.f + md5.a + g_k[i] + md5.buff[md5.g]; // str[md5.g]
			// md5.f = md5.f + md5.a + g_k[i] + str[md5.g];
			md5.a = md5.d;
			md5.d = md5.c;
			md5.c = md5.b;
			md5.b = md5.b + ft_b32rotate_left(md5.f, g_r[i]);

			ft_printf("%x %x %x %x\n", md5.a, md5.b, md5.c, md5.d);
		}

		md5.state[0] += md5.a;
		md5.state[1] += md5.b;
		md5.state[2] += md5.c;
		md5.state[3] += md5.d;

	}

	
	ft_printf("\n");
	printBits(md5.state, sizeof(uint32_t) * 4);
	for (int x = 0; x < 4; x++) {
		ft_printf("%x ", md5.state[x]);
		// md5.state[x] = ft_bswap32(md5.state[x]);
		// ft_printf("%ld\n", md5.state[x]);
	}

	ft_printf("\n\n");
	char digest[16] = {0};

	bitscounter_uint32(4);
	ft_printf("\n");

	// md5.state[0] = ft_bswap32(md5.state[0]);
	// md5.state[1] = ft_bswap32(md5.state[1]);
	// md5.state[2] = ft_bswap32(md5.state[2]);
	// md5.state[3] = ft_bswap32(md5.state[3]);

	ft_memcpy(digest, md5.state, 16);



	int i = -1;
	while (++i < 16)
		ft_printf("%02x ", digest[i] & 0xFF);
		// ft_printf("%02x ", ft_bswap8(digest[i]));

}
