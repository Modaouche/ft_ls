/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 01:07:15 by modaouch          #+#    #+#             */
/*   Updated: 2018/11/06 05:13:10 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OPT_H
# define FT_OPT_H
# include "ft_ls.h"

t_opt g_opt_tab[] =
{
	{"a", &ft_opt_hidden},
	{"l", &ft_opt_long},
	{"R", &ft_opt_recursive},
	{"r", &ft_opt_reverse},
	{"t", &ft_opt_time},
	{"G", &ft_opt_color},
	{"n", &ft_opt_num_info},
	{"i", &ft_opt_inode},
	{"S", &ft_opt_size},
	{"F", &ft_opt_symbol},
	{"d", &ft_opt_curr_dir},
	{"f", &ft_opt_unsorted},
	{"C", &ft_opt_column},
	{0, NULL}
};

#endif
