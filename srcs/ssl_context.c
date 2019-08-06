/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_context.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:47:34 by cchameyr          #+#    #+#             */
/*   Updated: 2019/08/06 21:38:35 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/header.h"

void		ssl_context(t_data *ssl)
{
	char	*str;
	char	**args;
	int		i;
	t_data	reset_ssl;

	ft_bzero((void **)&reset_ssl, sizeof(t_data));
	reset_ssl.sslcontext = true;
	ft_putstr("ft_ssl> ");
	ssl->sslcontext = true;
	while (get_next_line(0, &str) > 0)
	{
		args = ft_strsplit(str, ' ');
		i = ft_memlen((void **)args);
		*ssl = reset_ssl;
		handle_option(i, args, ssl);
		ft_memdel2((void ***)&args);
		ft_memdel((void **)&str);
		ft_putstr("ft_ssl> ");
	}
}
