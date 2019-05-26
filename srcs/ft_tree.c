/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 14:24:14 by modaouch          #+#    #+#             */
/*   Updated: 2018/11/06 05:04:05 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_long_list(t_dash **el, t_info *info_fld, int nbr, char btn)
{
	t_dash		*elem;

	elem = *el;
	ft_add_slash(el, info_fld->name[nbr], info_fld->path_root, btn);
	ft_add_stat(el, info_fld);
	elem->next_file = NULL;
	elem->next_level = NULL;
}

t_dash			*ft_btree_new(t_info *info_folders, int nbr, char btn)
{
	t_dash		*elem;

	if (!(elem = (t_dash*)malloc(sizeof(*elem))))
		ft_toexit(0, 0);
	elem->majmin[0] = 0;
	elem->majmin[1] = 0;
	elem->opt = info_folders->opt;
	elem->name = ft_strdup(info_folders->name[nbr]);
	ft_to_initialize(0, &elem);
	if (!(elem->opt & 2))
	{
		ft_add_slash(&elem, info_folders->name[nbr],\
		info_folders->path_root, btn);
		ft_tomode(&elem, info_folders, 0);
		if ((elem->opt & 16))
			ft_get_time(&elem, info_folders);
		lstat(elem->path, &(info_folders->statfile));
		if ((elem->opt & 512))
			ft_size_major_minor(&elem, info_folders->statfile);
	}
	else
		ft_long_list(&elem, info_folders, nbr, btn);
	return (elem);
}

void			ft_btree_add_file(t_dash **btree, t_info *info_folder, int nbr,\
				char btn)
{
	t_dash		*tmp;

	if (!*btree)
		*btree = ft_btree_new(info_folder, nbr, btn);
	else
	{
		tmp = ft_btree_new(info_folder, nbr, btn);
		if (tmp)
		{
			tmp->next_file = *btree;
			*btree = tmp;
		}
	}
}

void			ft_btree_push_front(t_dash **btree, t_dash **to_add)
{
	t_dash		*tmp;

	tmp = *to_add;
	if (tmp)
	{
		tmp->next_file = *btree;
		*btree = tmp;
	}
}

void			ft_btreedel(t_dash **btree)
{
	if ((*btree)->next_file)
		ft_btreedel(&(*btree)->next_file);
	if ((*btree)->next_level)
		ft_btreedel(&(*btree)->next_level);
	if (btree && *btree)
	{
		if ((*btree)->path)
			ft_strdel(&((*btree)->path));
		if ((*btree)->name)
			ft_strdel(&((*btree)->name));
		if ((*btree)->own_name)
			ft_strdel(&((*btree)->own_name));
		if ((*btree)->grp_name)
			ft_strdel(&((*btree)->grp_name));
		free(*btree);
	}
	*btree = NULL;
}
