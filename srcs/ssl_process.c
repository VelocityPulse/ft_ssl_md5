/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:47:34 by cchameyr          #+#    #+#             */
/*   Updated: 2019/07/11 18:30:03 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/header.h"

static void		read_stdin(t_data *ssl_data)
{
	char		*str;
	t_lststr	*stdin;

	while (get_next_line(0, &str) > 0) {
		ft_add_lststr(&stdin, str);
		ft_add_lststr(&stdin, "\n");
	}
	str = ft_merge_lststr(stdin);
	ft_lstadd(&(ssl_data->files_content), ft_lstnew(str, ft_strlen(str)));
}

static void 	read_files(t_data *ssl_data)
{
	t_lststr	*item_file;
	t_list		*lstnew;
	t_bin		*content;

	item_file = ssl_data->files_name;
	while (item_file)
	{
		content = ft_read_file(item_file->str);
		if (content == NULL)
			lstnew = ft_lstnew(NULL, 0);
		else
			lstnew = ft_lstnew(content->data, content->size);
		ft_lstadd(&(ssl_data->files_content), lstnew);
		item_file = item_file->next;
	}
}

void			get_content(t_data *ssl_data)
{
	if (ssl_data->files_name == NULL)
		read_stdin(ssl_data);
	else
		read_files(ssl_data);
}
