/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opt2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 21:06:14 by modaouch          #+#    #+#             */
/*   Updated: 2018/11/02 00:05:58 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_opt_color(int *opt)
{
	if (!(*opt & 32))
		*opt += 32;
}

void		ft_opt_num_info(int *opt)
{
	if (!(*opt & 128))
	{
		*opt += (!(*opt & 2)) ? 2 : 0;
		*opt -= ((*opt & 8192)) ? 8192 : 0;
		*opt += 128;
	}
}

void		ft_opt_inode(int *opt)
{
	if (!(*opt & 256))
		*opt += 256;
}

void		ft_opt_size(int *opt)
{
	if (!(*opt & 512))
	{
		*opt -= (*opt & 16) ? 16 : 0;
		*opt += 512;
	}
}

void		ft_opt_symbol(int *opt)
{
	if (!(*opt & 1024))
		*opt += 1024;
}
