/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:47:34 by cchameyr          #+#    #+#             */
/*   Updated: 2019/08/06 22:07:40 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/header.h"

static void		select_hash(t_content *content, t_data *ssl)
{
	ssl->turns++;
	if (content->content == NULL)
		ft_printf("ft_ssl: %s: No such file or directory\n", content->name);
	else if (ssl->hash == T_MD5)
		ft_md5(content, ssl);
	else if (ssl->hash == T_SHA256 || ssl->hash == T_SHA224)
		ft_sha2(content, ssl);
	if (content->origin == FILE)
	{
		if (content->size == 0)
			ft_memdel((void **)&content->content);
		else
			munmap(content->content, content->size);
	}
	else if (content->origin == STDIN_D || content->origin == STDIN_P ||
		content->origin == PARAM)
	{
		ft_memdel((void **)&content->content);
		ft_memdel((void **)&content->name);
	}
	ft_memdel((void *)&content);
}

static t_bool	handle_hash_option(char *arg, t_data *ssl)
{
	if (ft_strequ(arg, "-md5") || ft_strequ(arg, "md5"))
		ssl->hash = T_MD5;
	else if (ft_strequ(arg, "-sha256") || ft_strequ(arg, "sha256"))
		ssl->hash = T_SHA256;
	else if (ft_strequ(arg, "-sha224") || ft_strequ(arg, "sha224"))
		ssl->hash = T_SHA224;
	else
		return (false);
	return (true);
}

static t_bool	handle_param_option(char **av, int *i, t_data *ssl)
{
	t_content	*content;

	if (ft_strequ(av[*i], "-p"))
		select_hash(read_stdin(STDIN_P), ssl);
	else if (ft_strequ(av[*i], "-q"))
		ssl->q_flag = true;
	else if (ft_strequ(av[*i], "-r"))
		ssl->r_flag = true;
	else if (ft_strequ(av[*i], "-s") && !ssl->sslcontext)
	{
		if ((content = read_param(av[++(*i)])) == NULL)
			ft_printf("ft_ssl: option requires an argument --s\n%s\n", _USAGE_);
		else
			select_hash(content, ssl);
	}
	else
	{
		ft_putstr(ssl->sslcontext == true ? _USAGE_CONTEXT_ : _USAGE_);
		return (false);
	}
	return (true);
}

t_bool			handle_option(int ac, char **av, t_data *ssl)
{
	int			i;

	ssl->turns = 0;
	i = -1;
	while (++i < ac)
	{
		if (handle_hash_option(av[i], ssl))
			continue;
		if (av[i][0] != '-')
			break;
		if (!handle_param_option(av, &i, ssl))
			return (false);
	}
	i--;
	while (++i < ac)
		select_hash(read_file(av[i]), ssl);
	if (!ssl->turns)
		select_hash(read_stdin(STDIN_D), ssl);
	return (true);
}

int				main(int argc, char **argv)
{
	t_data		ssl;

	ft_bzero((void *)&ssl, sizeof(t_data));
	if (argc == 1)
	{
		ssl_context(&ssl);
		return (0);
	}
	handle_option(argc - 1, &(argv[1]), &ssl);
	return (0);
}
