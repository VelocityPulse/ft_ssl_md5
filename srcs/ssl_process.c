/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:47:34 by cchameyr          #+#    #+#             */
/*   Updated: 2019/07/31 16:41:09 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/header.h"

int				block_align64(int size)
{
	int a;

	a = ALIGN64(size);
	if (size >= a - 8)
		a += BLOCK_BYTE;
	return a;
}

static void		read_stdin(t_data *ssl)
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
	ssl->stdin = ft_memalloc(sizeof(t_bin));
	ssl->stdin->data = str;
	ssl->stdin->size = len;
}

static t_list	*alloc_file(char *path, t_data *ssl)
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

static void 	read_files(t_data *ssl)
{
	t_lststr	*item_file;
	t_list		*lstnew;

	item_file = ssl->files_name;
	while (item_file)
	{
		lstnew = alloc_file(item_file->str, ssl);
		ft_lstadd(&(ssl->files_content), lstnew);
		item_file = item_file->next;
	}
}

void			get_content(t_data *ssl)
{
	ssl->files_content = NULL;
	ssl->stdin = NULL;

	if (ssl->files_name == NULL || ssl->p_flag)
		read_stdin(ssl);
	if (ssl->files_name != NULL)
		read_files(ssl);
}
