/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opt3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 21:06:14 by modaouch          #+#    #+#             */
/*   Updated: 2018/11/02 00:08:54 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_opt_curr_dir(int *opt)
{
	if (!(*opt & 2048))
		*opt += 2048;
}

void		ft_opt_unsorted(int *opt)
{
	if (!(*opt & 4096))
	{
		*opt += (!(*opt & 1)) ? 1 : 0;
		*opt += 4096;
	}
}

void		ft_opt_column(int *opt)
{
	if (!(*opt & 8192))
	{
		*opt -= (*opt & 2) ? 2 : 0;
		*opt += 8192;
	}
}

int			ft_cycle(t_dash *tmp)
{
	int		i;

	if (tmp)
	{
		i = ft_strlen(tmp->path);
		if (i > 1 && tmp->path[i - 1] == '/')
			i -= 2;
		while (i > 0 && (tmp->path[i] != '/'))
			i--;
		if (tmp->path[i] == '/')
			if (!ft_strcmp(&(tmp->path[i + 1]), ".") ||\
			!ft_strcmp(&(tmp->path[i + 1]), ".."))
				return (1);
	}
	return (0);
}
