/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opt1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 21:06:14 by modaouch          #+#    #+#             */
/*   Updated: 2018/11/02 00:05:28 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_opt_hidden(int *opt)
{
	if (!(*opt & 1))
		*opt += 1;
}

void		ft_opt_long(int *opt)
{
	if (!(*opt & 2))
	{
		*opt -= (*opt & 8192) ? 8192 : 0;
		*opt += 2;
	}
}

void		ft_opt_recursive(int *opt)
{
	if (!(*opt & 4))
		*opt += 4;
}

void		ft_opt_reverse(int *opt)
{
	if (!(*opt & 8))
		*opt += 8;
}

void		ft_opt_time(int *opt)
{
	if (!(*opt & 16) && !(*opt & 512))
		*opt += 16;
}
