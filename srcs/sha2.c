/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:47:34 by cchameyr          #+#    #+#             */
/*   Updated: 2019/07/28 12:09:37 by cchameyr         ###   ########.fr       */
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

static void printBits(void const * const ptr, size_t size)
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

void		ft_sha2(t_data *ssl_data, char *str, int len)
{
	t_sha2	sha2;
	char	digest[32] = {0};

	sha2.state[0] = 0x6a09e667;
	sha2.state[1] = 0xbb67ae85;
	sha2.state[2] = 0x3c6ef372;
	sha2.state[3] = 0xa54ff53a;
	sha2.state[4] = 0x510e527f;
	sha2.state[5] = 0x9b05688c;
	sha2.state[6] = 0x1f83d9ab;
	sha2.state[7] = 0x5be0cd19;

	str[len] = -128;
	// ((uint64_t *)s)[sha2->aligned64 / 8 - 1] = len * 8;

	printBits(str, ALIGN64(len));


}
