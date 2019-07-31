/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:47:34 by cchameyr          #+#    #+#             */
/*   Updated: 2019/07/31 16:54:07 by cchameyr         ###   ########.fr       */
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

static t_bool	handle_param_option(char *arg, t_data *ssl)
{
	if (ft_strequ(arg, "-p"))
		ssl->p_flag = true;
	else if (ft_strequ(arg, "-q"))
		ssl->q_flag = true;
	else if (ft_strequ(arg, "-r"))
		ssl->r_flag = true;
	else if (ft_strequ(arg, "-s"))
		ssl->s_flag = true;
	else
		return false;
	return true;
}

static t_bool	handle_option(int ac, char **av, t_data *ssl)
{
	int		i;

	ssl->hash_flag = T_MD5;
	i = 0;
	while (++i < ac)
	{
		if (av[i][0] == '-')
		{
			if (handle_hash_option(av[i], ssl) == true)
				continue;
			if (handle_param_option(av[i], ssl) == false)
			{
				ft_putstr(_USAGE_);
				return false;
			}
		} else
			break;
	}
	while (i < ac)
		ft_add_lststr(&(ssl->files_name), av[i++]);
	return true;
}

void		select_hash(void *content, int size, char *name, t_data *ssl)
{
	if (content == NULL)
		ft_printf("failed to read\n");
	else if (ssl->hash_flag == T_MD5)
		ft_md5(content, size, name, ssl);
	else if (ssl->hash_flag == T_SHA256)
		ft_sha2(content, size, name, ssl);
}

int			main(int argc, char **argv)
{
	t_data		ssl;
	t_list		*content;
	t_lststr	*files_name;

	if (handle_option(argc, argv, &ssl) == true)
	{
		get_content(&ssl);
		files_name = ssl.files_name;
		content = ssl.files_content;
		if (ssl.files_content == NULL || ssl.p_flag)
			select_hash(ssl.stdin->data, ssl.stdin->size, NULL, &ssl);
		while (content)
		{
			select_hash(content->content, content->content_size,
				files_name->str, &ssl);
			content = content->next;
			files_name = files_name->next;
		}
	}
	return (0);
}
