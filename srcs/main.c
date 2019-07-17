/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:47:34 by cchameyr          #+#    #+#             */
/*   Updated: 2019/07/16 18:41:31 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/header.h"

t_bool	handle_hash_option(char *arg, t_data *ssl_data)
{
	if (ft_strequ(arg, "-md5"))
		ssl_data->hash_flag = T_MD5;
	else if (ft_strequ(arg, "-sha256"))
		ssl_data->hash_flag = T_SHA256;
	else
		return false;
	return true;
}

t_bool handle_param_option(char *arg, t_data *ssl_data)
{
	if (ft_strequ(arg, "-p"))
		ssl_data->p_flag = true;
	else if (ft_strequ(arg, "-q"))
		ssl_data->q_flag = true;
	else if (ft_strequ(arg, "-r"))
		ssl_data->r_flag = true;
	else if (ft_strequ(arg, "-s"))
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
	return true;
}

int		main(int argc, char **argv)
{
	t_data	ssl_data;
	t_list	*content;

	if (handle_option(argc, argv, &ssl_data) == true)
	{
		get_content(&ssl_data);
		content = ssl_data.files_content;
		while (content)	
		{
			if (content->content == NULL)
				ft_printf("failed to read\n");
			else if (ssl_data.hash_flag == T_MD5)
				ft_md5_handle(&ssl_data, content->content, content->content_size);

			content = content->next;
		}
	}
	return (0);
}
