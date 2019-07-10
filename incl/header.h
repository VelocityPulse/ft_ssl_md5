/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:47:34 by cchameyr          #+#    #+#             */
/*   Updated: 2019/07/10 19:00:21 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HEADER_H

# include "../libft/libft.h"
# include <stdlib.h>

# define _USAGE_ "Usage: [-md5 -sha256] [-p -q -r -s] [file]\n"

typedef enum	e_hashflag
{
	T_MD5,
	T_SHA256,
	NB_TYPE,
}				t_hashflag;

typedef struct	s_data
{
	t_hashflag	hash_flag;
	t_bool		p_flag;
	t_bool		q_flag;
	t_bool		r_flag;
	t_bool		s_flag;
	t_lststr	*files_name;
	t_list		*files_content;
}				t_data;

void		ft_md5_handle(t_data *ssl_data);

void		get_content(t_data *ssl_data);

#endif
