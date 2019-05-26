/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filling.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:45:07 by modaouch          #+#    #+#             */
/*   Updated: 2018/11/06 04:37:51 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_print_path(t_dash *tmp, int *nbfile, int *i, int btn)
{
	if (nbfile[0])
		ft_printf("\n%s:\n", tmp->path);
	else if (nbfile[1] > 1)
		ft_printf("%s:\n", tmp->path);
	if (btn)
		*i = 0;
	if (tmp->opt & 4 && btn)
	{
		nbfile[0] = 1;
		nbfile[1] = 1;
	}
	if (btn)
		(!(tmp->to_open = opendir(tmp->path))) ? ft_toexit(0, 0) : 0;
}

static void		ft_fill(t_dash **btree, t_info *info_folders, int *i, int *sp)
{
	t_dash		*tmp;

	tmp = *btree;
	info_folders->name[*i] = 0;
	((closedir(tmp->to_open) == -1)) ? ft_toexit(1, tmp->path) : 0;
	info_folders->path_root = ft_strdup(tmp->path);
	ft_insert_wave(&(tmp->next_level), info_folders, 0);
	*i = 0;
	ft_sorting_choice(&tmp->next_level, i);
	ft_how_many_sp(&(tmp->next_level), sp);
	ft_print(&(tmp->next_level), sp, 1);
	(info_folders->path_root) ? free(info_folders->path_root) : 0;
	info_folders->path_root = NULL;
}

void			ft_simple_fill_it(t_dash **btree, t_info *info_fld, int *nbfile)
{
	t_dash		*tmp;
	int			nb_elem;
	int			sp[8];
	int			i;

	tmp = *btree;
	while (tmp)
	{
		nb_elem = ft_nb_elem(tmp, nbfile);
		if (nb_elem && (tmp->type_chmod[0] == 'd'))
		{
			ft_print_path(tmp, nbfile, &i, 1);
			ft_free_name_folders(info_fld);
			(!(info_fld->name = (char **)malloc(sizeof(char *)\
			* (nb_elem + 1)))) ? ft_toexit(0, 0) : 0;
			while ((info_fld->infodirent = readdir(tmp->to_open)))
				info_fld->name[i++] = ft_strdup(info_fld->infodirent->d_name);
			ft_fill(&tmp, info_fld, &i, sp);
			if (tmp->next_file)
				ft_putendl("");
		}
		tmp = tmp->next_file;
	}
	ft_btreedel(btree);
}

void			ft_recursive_fill_it(t_dash **btree, t_info *info_fld,\
				int *nbfile, int first)
{
	t_dash		*tmp;
	int			nb_elem;
	int			i;
	int			sp[8];

	tmp = *btree;
	while (tmp)
	{
		nb_elem = (ft_link_to_doss(tmp)) ? 0 : ft_nb_elem(tmp, nbfile);
		if (nb_elem && (tmp->type_chmod[0] == 'd') &&\
			(ft_hidden_face(tmp) || first) && ((ft_cycle(tmp) != 1) || first))
		{
			ft_print_path(tmp, nbfile, &i, 1);
			ft_free_name_folders(info_fld);
			(!(info_fld->name = (char **)malloc(sizeof(char *)\
			* (nb_elem + 1)))) ? ft_toexit(0, 0) : 0;
			while ((info_fld->infodirent = readdir(tmp->to_open)))
				info_fld->name[i++] = ft_strdup(info_fld->infodirent->d_name);
			ft_fill(&tmp, info_fld, &i, sp);
			ft_recursive_fill_it(&(tmp->next_level), info_fld,\
			nbfile, 0);
		}
		tmp = tmp->next_file;
	}
	ft_btreedel(btree);
}
