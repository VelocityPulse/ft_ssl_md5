/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:47:34 by cchameyr          #+#    #+#             */
/*   Updated: 2019/07/31 15:30:25 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/header.h"

int				block_align64(int size)
{
	int a; // segfault sur une lecture d'un touch

	a = ALIGN64(size);
	if (size >= a - 8)
		a += BLOCK_BYTE;
	return a;
}

static void		read_stdin(t_data *ssl_data)
{
	char		*str;
	char		*tmp;
	int			len;
	t_lststr	*stdin;

	len = 0;
	stdin = NULL;
	while (get_next_line(0, &str) > 0)
	{
		ft_add_lststr(&stdin, str);
		ft_add_lststr(&stdin, "\n");
		len += ft_strlen(str) + 1;
	}
	tmp = ft_merge_lststr(stdin);
	str = ft_strnew(block_align64(len));
	ft_memcpy(str, tmp, len);
	ft_memdel((void **)&tmp);
	ft_lstadd(&(ssl_data->files_content), ft_lstnew(str, len));
}

static t_list	*alloc_file(char *path, t_data *ssl_data)
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
	if (buff.st_size == 0)
		ptr = ft_memalloc(block_align64(buff.st_size));
	else
		ptr = mmap(0, block_align64(buff.st_size), PROT_WRITE, MAP_PRIVATE, fd, 0);
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
		lstnew = alloc_file(item_file->str, ssl_data);
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
