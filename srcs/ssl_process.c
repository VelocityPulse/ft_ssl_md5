/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:47:34 by cchameyr          #+#    #+#             */
/*   Updated: 2019/07/10 17:35:49 by cchameyr         ###   ########.fr       */
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
	ft_add_lststr(&(ssl_data->files_content), str);
}

void			get_content(t_data *ssl_data)
{
	if (ssl_data->files_name == NULL)
		read_stdin(ssl_data);
}
