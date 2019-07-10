/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:47:34 by cchameyr          #+#    #+#             */
/*   Updated: 2019/07/10 14:56:44 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HEADER_H

# include "../libft/libft.h"

# define _USAGE_ "Usage: [-md5 -sha256] [-pqrs] [file]\n"

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
	t_lststr	*files_content;
}				t_data;


#endif
