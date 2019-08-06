/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:47:34 by cchameyr          #+#    #+#             */
/*   Updated: 2019/08/06 23:28:24 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/header.h"

int				block_align64(int size)
{
	int a;

	a = ALIGN64(size);
	if (size >= a - 8)
		a += BLOCK_BYTE;
	return (a);
}

t_content		*read_param(char *param)
{
	t_content	*content;
	char		*str;
	int			len;

	content = (t_content *)ft_memalloc(sizeof(t_content));
	content->origin = PARAM;
	if (param == NULL)
		return (content);
	len = ft_strlen(param);
	str = ft_strnew(block_align64(len));
	ft_strcpy(str, param);
	content->content = str;
	content->size = len;
	content->name = ft_strdup(param);
	return (content);
}

t_content		*read_stdin(t_origin origin)
{
	char		*str;
	t_lststr	*stdin;
	t_content	*content;

	stdin = NULL;
	content = (t_content *)ft_memalloc(sizeof(t_content));
	content->origin = origin;
	content->size = 0;
	while (get_next_line(0, &str) > 0)
	{
		ft_add_lststr(&stdin, str);
		ft_add_lststr(&stdin, ft_strdup("\n"));
		content->size += ft_strlen(str) + 1;
	}
	ft_memdel((void **)&str);
	str = ft_merge_lststr(stdin);
	content->content = ft_strnew(block_align64(content->size));
	ft_memcpy(content->content, str, content->size);
	ft_memdel((void **)&str);
	content->name = ft_strdup(content->content);
	if (content->size > 0)
		content->name[content->size - 1] = 0;
	ft_lststr_del(&stdin);
	return (content);
}

t_content		*read_file(char *path)
{
	int			fd;
	void		*ptr;
	struct stat	buff;
	t_content	*content;

	content = (t_content *)ft_memalloc(sizeof(t_content));
	content->name = path;
	content->origin = FILE;
	if ((fd = open(path, O_RDONLY)) < 0)
		return (content);
	if (fstat(fd, &buff) < 0)
		return (content);
	if (buff.st_size == 0)
		ptr = ft_memalloc(block_align64(buff.st_size));
	else
		ptr = mmap(0, block_align64(buff.st_size),
				PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (ptr == MAP_FAILED)
		return (content);
	content->content = ptr;
	content->size = buff.st_size;
	close(fd);
	return (content);
}

void			parse_help(t_content *content, char *hash, t_data *ssl)
{
	if (!ssl->r_flag)
	{
		if (content->origin == PARAM)
			ft_printf("%s (\"%s\") = ", hash, content->name);
		else if (content->origin == FILE)
			ft_printf("%s (%s) = ", hash, content->name);
	}
	else
	{
		if (content->origin == PARAM)
			ft_printf(" \"%s\"\n", content->name);
		else if (content->origin == FILE)
			ft_printf(" %s\n", content->name);
	}
}
