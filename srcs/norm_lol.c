/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_lol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:47:34 by cchameyr          #+#    #+#             */
/*   Updated: 2020/03/03 11:21:53 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/header.h"

char	*usg(void)
{
	return ("Usage : [-md5 -sha224 -sha256 -sha384 -sha512] "
	"[-p -q -r -s] [file]\n");
}

char	*usg_c(void)
{
	return ("Usage in context : [-md5 -sha224 -sha256 -sha384 -sha512] "
	"[-p -q -r] [file]\n");
}

int		align_64(int size)
{
	return (((size - 1) + 64) - ((size - 1) % 64));
}

int		align_128(int size)
{
	return (((size - 1) + 128) - ((size - 1) % 128));
}
