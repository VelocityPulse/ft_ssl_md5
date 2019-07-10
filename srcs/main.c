/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:47:34 by cchameyr          #+#    #+#             */
/*   Updated: 2019/07/10 15:43:47 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/header.h"

t_bool	handle_hash_option(char *arg, t_data *ssl_data)
{
	if (ft_strcmp(arg, "-md5") == _CMP_EQUAL_)
		ssl_data->hash_flag = T_MD5;
	else if (ft_strcmp(arg, "-sha256") == _CMP_EQUAL_)
		ssl_data->hash_flag = T_SHA256;
	else
		return false;
	return true;
}

t_bool handle_param_option(char *arg, t_data *ssl_data)
{
	if (ft_strcmp(arg, "-p") == _CMP_EQUAL_)
		ssl_data->p_flag = true;
	else if (ft_strcmp(arg, "-q") == _CMP_EQUAL_)
		ssl_data->q_flag = true;
	else if (ft_strcmp(arg, "-r") == _CMP_EQUAL_)
		ssl_data->r_flag = true;
	else if (ft_strcmp(arg, "-s") == _CMP_EQUAL_)
		ssl_data->s_flag = true;
	else
		return false;
	return true;
}

t_bool	handle_option(int ac, char **av, t_data *ssl_data)
{
	int		i;

	ssl_data->hash_flag = T_MD5;
	i = 0;
	while (++i < ac)
	{
		if (av[i][0] == '-')
		{
			if (handle_hash_option(av[i], ssl_data) == true)
				continue;
			if (handle_param_option(av[i], ssl_data) == false) {
				ft_printf(_USAGE_);
				return false;
			}
		} else
			break;
	}
	while (i < ac)
		ft_add_lststr(&(ssl_data->files_name), av[i++]);
	ft_print_lststr(ssl_data->files_name);
	return true;
}

int		main(int argc, char **argv)
{
	t_data	ssl_data;

	if (argc < 2)
	{
		ft_printf(_USAGE_);
		return (_ERROR_);
	}
	if (handle_option(argc, argv, &ssl_data) == true)
	{
		if (ssl_data.hash_flag == T_MD5)
			ft_md5(&ssl_data);
	}
	return (0);
}
