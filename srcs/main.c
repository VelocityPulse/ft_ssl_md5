/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:47:34 by cchameyr          #+#    #+#             */
/*   Updated: 2019/07/31 19:57:31 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/header.h"

static t_bool	handle_hash_option(char *arg, t_data *ssl)
{
	if (ft_strequ(arg, "-md5"))
		ssl->hash_flag = T_MD5;
	else if (ft_strequ(arg, "-sha256") || ft_strequ(arg, "-sha2"))
		ssl->hash_flag = T_SHA256;
	else
		return false;
	return true;
}

static void		select_hash(t_content *content, t_data *ssl)
{
	if (content == NULL)
		ft_printf("ft_ssl: %s: No such file or directory\n", content->name);
	else if (ssl->hash_flag == T_MD5)
		ft_md5(content, ssl);
	else if (ssl->hash_flag == T_SHA256)
		ft_sha2(content, ssl);
}

static t_bool	handle_param_option(int ac, char **av, int *i, t_data *ssl)
{
	t_content	*content;
	if (ft_strequ(av[*i], "-p"))
		select_hash(read_stdin(), ssl);
	else if (ft_strequ(av[*i], "-q"))
		ssl->q_flag = true;
	else if (ft_strequ(av[*i], "-r"))
		ssl->r_flag = true;
	else if (ft_strequ(av[*i], "-s"))
	{
		if ((content = read_param(av[++(*i)])) == NULL)
			ft_printf("ft_ssl: option requires an argument --s\n%s\n", _USAGE_);
		else
			select_hash(content, ssl);
	}
	else
	{
		ft_putstr(_USAGE_);
		return false;
	}
	return true;
}

static t_bool	handle_option(int ac, char **av, t_data *ssl)
{
	int			i;
	t_content	*content;

	i = 0;
	while (++i < ac && av[i][0] == '-')
	{
		// if (av[i][0] == '-')
		// {
			if (handle_hash_option(av[i], ssl) == true)
				continue;
			if (handle_param_option(ac, av, &i, ssl) == false)
				return false;
		// } else
		// 	break;
	}
	i--;
	while (++i < ac)
	{
		if (!(content = read_file(av[i])))
			ft_printf("ft_ssl: %s: No such file or directory\n", av[i]);
		else
			select_hash(content, ssl);
	}
	return true;
}

int			main(int argc, char **argv)
{
	t_data		ssl;
	// t_list		*contents;
	// t_content	*item;

	ft_bzero((void *)&ssl, sizeof(t_data));
	handle_option(argc, argv, &ssl);

	return (0);
}
