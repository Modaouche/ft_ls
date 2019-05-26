/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 11:25:49 by modaouch          #+#    #+#             */
/*   Updated: 2018/11/02 10:13:50 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_print_color(t_dash **btree, int *sp, int nbsp)
{
	t_dash	*bt;

	bt = *btree;
	nbsp = conv_sp(bt, sp, 7);
	(bt->opt & 256) ? ft_printf("%nd ", conv_sp(bt, sp, 4), bt->inod) : 0;
	if (bt->opt & 2)
		(bt->type_chmod[0] != 'c' && bt->type_chmod[0] != 'b') ?\
		ft_printf("%s %nd %s  %ns %n %nd %s %s", bt->type_chmod,\
		conv_sp(bt, sp, 0), bt->physical_link, bt->own_name,\
		conv_sp(bt, sp, 1), bt->grp_name, conv_sp(bt, sp, 2),\
		(conv_sp(bt, sp, 3) + conv_sp(bt, sp, 6) + conv_sp(bt, sp, 5)),\
		bt->size, bt->tea_time, ft_color(&bt)) :\
		ft_printf("%s %nd %s  %ns %n %nd, %nd %s %s",\
		bt->type_chmod, conv_sp(bt, sp, 0), bt->physical_link,\
		bt->own_name, conv_sp(bt, sp, 1), bt->grp_name,\
		conv_sp(bt, sp, 2), conv_sp(bt, sp, 5), bt->majmin[0],\
		conv_sp(bt, sp, 6), bt->majmin[1], bt->tea_time, ft_color(&bt));
	else
	{
		ft_printf("%s", ft_color(&bt));
		((bt->opt & 8192)) ? ft_printf(" %n", nbsp) : 0;
	}
	if (bt->type_chmod[0] == 'l' && bt->opt & 2 && bt->link[0])
		ft_printf(" -> %s", bt->link);
	(!(bt->opt & 8192)) ? ft_putendl("") : 0;
}

static void	ft_print_simple(t_dash **btree, int *sp)
{
	t_dash	*bt;

	bt = *btree;
	(bt->opt & 256) ? ft_printf("%nd ", conv_sp(bt, sp, 4), bt->inod) : 0;
	if (bt->opt & 2)
		(bt->type_chmod[0] != 'c' && bt->type_chmod[0] != 'b') ?\
		ft_printf("%s %nd %s  %ns %n %nd %s %s", bt->type_chmod,\
		conv_sp(bt, sp, 0), bt->physical_link, bt->own_name,\
		conv_sp(bt, sp, 1), bt->grp_name, conv_sp(bt, sp, 2),\
		(conv_sp(bt, sp, 3) + conv_sp(bt, sp, 6) + conv_sp(bt, sp, 5)),\
		bt->size, bt->tea_time, bt->name) :\
		ft_printf("%s %nd %s  %ns %n %nd, %nd %s %s",\
		bt->type_chmod, conv_sp(bt, sp, 0), bt->physical_link,\
		bt->own_name, conv_sp(bt, sp, 1), bt->grp_name,\
		conv_sp(bt, sp, 2), conv_sp(bt, sp, 5), bt->majmin[0],\
		conv_sp(bt, sp, 6), bt->majmin[1], bt->tea_time, bt->name);
	else
	{
		ft_printf("%s", bt->name);
		if ((bt->opt & 8192))
			ft_printf(" %n", conv_sp(bt, sp, 7));
	}
	if (bt->type_chmod[0] == 'l' && bt->opt & 2 && bt->link[0])
		ft_printf(" -> %s", bt->link);
	(!(bt->opt & 8192)) ? ft_putendl("") : 0;
}

void		ft_column_file(t_dash **print_btree, t_dash *bt, int *sp, int i)
{
	t_dash	*tmp;
	int		offset;
	int		column;
	int		count;

	tmp = *print_btree;
	count = ft_wave_len(*print_btree);
	column = ft_nbcolumn(sp);
	offset = ft_get_offset(bt, column);
	while (bt)
	{
		if (tmp && tmp->type_chmod[0] != 'd')
			(bt->opt & 32) ? ft_print_color(&tmp, sp, 0) :\
				ft_print_simple(&tmp, sp);
		if ((i++ == column || ft_wave_len(tmp) < offset))
		{
			if (!ft_next_line(&bt, &tmp, &count, &i))
				break ;
			continue ;
		}
		if (!--count)
			break ;
		ft_offset(&tmp, offset);
	}
}

void		ft_column(t_dash **print_btree, t_dash *bt, int *sp, int i)
{
	t_dash	*tmp;
	int		off_col[2];
	int		count;

	tmp = ft_init_column_var(print_btree, sp, off_col, &count);
	off_col[0] = ft_get_offset_hidden(bt, off_col[1]);
	while (bt)
	{
		if (ft_hidden_face(tmp) == 1 && ft_hidden_face(bt) == 1)
			(tmp->opt & 32) ? ft_print_color(&tmp, sp, 0) :\
				ft_print_simple(&tmp, sp);
		if (ft_hidden_face(tmp))
		{
			if ((i++ == off_col[1] || ft_wave_len_hidden(tmp) < off_col[0]))
			{
				if (!ft_next_line(&bt, &tmp, &count, &i))
					break ;
				continue ;
			}
			if (!count--)
				break ;
		}
		if (!ft_next_column(&bt, &tmp, count, off_col))
			break ;
	}
}

void		ft_print(t_dash **print_btree, int *sp, int btn)
{
	t_dash	*bt;

	bt = *print_btree;
	if (bt->opt & 8192 && !(bt->opt & 2048))
	{
		(btn == 1) ? ft_column(print_btree, *print_btree, sp, 1) :\
		ft_column_file(print_btree, *print_btree, sp, 1);
		(btn == 0) ? ft_putendl("") : 0;
		return ;
	}
	if (!(bt->opt & 2048) && btn == 1)
		ft_total(*print_btree);
	while (bt)
	{
		if ((btn == 1) && (ft_hidden_face(bt) || bt->opt & 2048))
			(bt->opt & 32) ? ft_print_color(&bt, sp, 0) :\
			ft_print_simple(&bt, sp);
		else if ((btn == 0) && bt->type_chmod[0] != 'd')
			(bt->opt & 32) ? ft_print_color(&bt, sp, 0) :\
			ft_print_simple(&bt, sp);
		bt = bt->next_file;
	}
}
