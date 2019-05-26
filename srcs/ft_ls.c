/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 14:24:14 by modaouch          #+#    #+#             */
/*   Updated: 2018/11/02 11:23:50 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <grp.h>

int				ft_nbfile(t_dash *btree)
{
	int			nb;

	nb = 0;
	while (btree)
	{
		if (btree->type_chmod[0] != 'd')
			nb++;
		btree = btree->next_file;
	}
	return (nb);
}

int				ft_nbfold(t_dash *btree)
{
	int			nb;

	nb = 0;
	while (btree)
	{
		if (btree->type_chmod[0] == 'd')
			nb++;
		btree = btree->next_file;
	}
	return (nb);
}

void			ft_insert_wave(t_dash **btree, t_info *info_folders, char btn)
{
	int			nbr;

	nbr = 0;
	while (info_folders->name[nbr])
	{
		ft_btree_add_file(btree, info_folders, nbr, btn);
		nbr++;
	}
}

void			ft_ls(t_dash **btree, t_info *info_folders)
{
	int			not_first;
	int			sp[8];
	int			nbfile[2];

	ft_insert_wave(btree, info_folders, 1);
	nbfile[0] = ft_nbfile(*btree);
	nbfile[1] = ft_nbfold(*btree);
	not_first = 0;
	ft_sorting_choice(btree, &not_first);
	ft_how_many_sp(btree, sp);
	not_first = ft_wave_len(*btree);
	if ((*btree)->opt & 2048 && not_first)
	{
		ft_print(btree, sp, 1);
		(((*btree)->opt & 8192)) ? ft_putendl("") : 0;
		ft_btreedel(btree);
		return ;
	}
	if (not_first > 1 || (not_first > 0 && (*btree)->type_chmod[0] != 'd'))
		ft_print(btree, sp, 0);
	if (!(info_folders->opt & 4))
		ft_simple_fill_it(btree, info_folders, nbfile);
	else
		ft_recursive_fill_it(btree, info_folders, nbfile, 1);
}
