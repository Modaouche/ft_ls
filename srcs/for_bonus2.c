/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_bonus2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 05:29:08 by modaouch          #+#    #+#             */
/*   Updated: 2018/11/02 09:19:33 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					ft_get_offset(t_dash *bt, int column)
{
	return ((ft_wave_len(bt) / column) + 1);
}

int					ft_get_offset_hidden(t_dash *bt, int column)
{
	return ((ft_wave_len_hidden(bt) / column) + 1);
}

t_dash				**ft_offset_hidden(t_dash **bt, int offset)
{
	t_dash			**tmp;

	tmp = bt;
	if (!bt || !*bt)
		return (0);
	if ((*bt)->opt & 8192)
		while ((*tmp) && offset)
		{
			if (ft_hidden_face(*tmp) == 1)
				offset--;
			*tmp = (*tmp)->next_file;
		}
	if (offset > 0)
		return (0);
	return (tmp);
}

t_dash				**ft_offset(t_dash **bt, int offset)
{
	t_dash			**tmp;

	tmp = bt;
	if (!bt || !*bt)
		return (0);
	if ((*bt)->opt & 8192)
		while ((*tmp) && offset)
		{
			offset--;
			*tmp = (*tmp)->next_file;
		}
	if (offset > 0)
		return (0);
	return (tmp);
}

int					ft_nbcolumn(int *sp)
{
	struct winsize	windows;
	int				len;
	int				col;
	int				sum;

	sum = sp[7] + 3;
	len = 0;
	col = 0;
	ioctl(0, TIOCGWINSZ, &windows);
	while ((len + sum) <= windows.ws_col)
	{
		len = len + sum;
		col++;
	}
	if (col == 0)
		return (1);
	return (col);
}
