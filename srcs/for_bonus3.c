/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_bonus3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 12:24:48 by modaouch          #+#    #+#             */
/*   Updated: 2018/11/02 04:32:56 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_symbol_file(t_dash **element)
{
	t_dash	*bt;
	char	c[2];

	c[0] = 0;
	c[1] = 0;
	bt = *element;
	(bt->type_chmod[0] == 'd') ? c[0] = '/' : 0;
	(bt->type_chmod[0] == 'l') ? c[0] = '@' : 0;
	(bt->type_chmod[0] == 's') ? c[0] = '=' : 0;
	(bt->type_chmod[0] == 'p') ? c[0] = '|' : 0;
	(bt->type_chmod[0] == '-' && ((bt->type_chmod[3] == 'x') ||\
	((bt->type_chmod[6] == 'x') || (bt->type_chmod[9] == 'x')))) ?\
	c[0] = '*' : 0;
	bt->name = ft_strjoin_free(bt->name, c, 1);
}

t_dash		*ft_init_column_var(t_dash **print_btree, int *sp, int *off_col,\
			int *count)
{
	*count = ft_wave_len_hidden(*print_btree);
	off_col[1] = ft_nbcolumn(sp);
	off_col[0] = ft_get_offset_hidden(*print_btree, off_col[1]);
	return (*print_btree);
}

int			ft_next_line(t_dash **btree, t_dash **tmp, int *count, int *i)
{
	*btree = (*btree)->next_file;
	*tmp = *btree;
	*i = 1;
	ft_putendl("");
	*count -= 1;
	if (*count <= 0)
		return (0);
	return (1);
}

int			ft_next_column(t_dash **bt, t_dash **tmp, int count, int *off_col)
{
	if (!bt)
		if (!count)
			return (0);
	(!ft_hidden_face(*bt)) ? *bt = (*bt)->next_file : 0;
	if (!ft_hidden_face(*tmp))
		*tmp = (*tmp)->next_file;
	else
		ft_offset_hidden(tmp, off_col[0]);
	return (1);
}
