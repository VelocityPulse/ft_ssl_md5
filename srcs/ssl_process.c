/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:47:34 by cchameyr          #+#    #+#             */
/*   Updated: 2019/07/18 19:15:17 by cchameyr         ###   ########.fr       */
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

static t_list	*read_file(char *path)
{
	int			fd;
	void		*ptr;
	struct stat	buff;
	t_list		*data;

	data = (t_list *)ft_memalloc(sizeof(t_list));
	if ((fd = open(path, O_RDONLY)) < 0)
		return data;
	if (fstat(fd, &buff) < 0)
		return data;
	ptr = mmap(0, LENGHT_ALIGN(buff.st_size), PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (ptr == MAP_FAILED)
		return data;
	data->content = ptr;
	data->content_size = buff.st_size;
	return data;
}

static void 	read_files(t_data *ssl_data)
{
	t_lststr	*item_file;
	t_list		*lstnew;

	item_file = ssl_data->files_name;
	while (item_file)
	{
		lstnew = read_file(item_file->str);
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
