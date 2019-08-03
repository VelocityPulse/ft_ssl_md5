/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:47:34 by cchameyr          #+#    #+#             */
/*   Updated: 2019/08/03 18:57:40 by cchameyr         ###   ########.fr       */
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

	if (param == NULL)
		return (NULL);
	content = (t_content *)ft_memalloc(sizeof(t_content));
	len = ft_strlen(param);
	str = ft_strnew(block_align64(len));
	ft_strcpy(str, param);
	content->content = str;
	content->size = len;
	content->origin = PARAM;
	content->name = ft_strdup(param);
	return (content);
}

t_content		*read_stdin(t_origin origin)
{
	char		*str;
	char		*tmp;
	int			len;
	t_lststr	*stdin;
	t_content	*content;

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
	content = (t_content *)ft_memalloc(sizeof(t_content));
	content->content = str;
	content->size = len;
	content->name = ft_strdup(str);
	content->origin = origin;
	content->name[len - 1] = 0;
	return (content);
}

t_content		*read_file(char *path)
{
	int			fd;
	void		*ptr;
	struct stat	buff;
	t_content	*content;

	if ((fd = open(path, O_RDONLY)) < 0)
		return (NULL);
	if (fstat(fd, &buff) < 0)
		return (NULL);
	if (buff.st_size == 0)
		ptr = ft_memalloc(block_align64(buff.st_size));
	else
		ptr = mmap(0, block_align64(buff.st_size),
				PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
	content = (t_content *)ft_memalloc(sizeof(t_content));
	content->content = ptr;
	content->size = buff.st_size;
	content->name = path;
	content->origin = FILE;
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
