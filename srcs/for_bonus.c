/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 12:13:33 by modaouch          #+#    #+#             */
/*   Updated: 2018/11/02 08:36:20 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_color_dir_reg(t_dash **btree, struct stat stf, int button)
{
	t_dash		*bt;

	bt = *btree;
	if (button == 0)
	{
		bt->name = ((!(S_ISGID & stf.st_mode) && !(S_ISUID & stf.st_mode))) ?\
			ft_strjoin_free(RED, bt->name, 2) :\
			ft_strjoin_free(BK, bt->name, 2);
		(S_ISUID & stf.st_mode) ?\
			bt->name = ft_strjoin_free(RED_S, bt->name, 2) : 0;
		(!(S_ISUID & stf.st_mode) && (S_ISGID & stf.st_mode)) ?\
			bt->name = ft_strjoin_free(CYAN_S, bt->name, 2) : 0;
	}
	else
	{
		bt->name = (!(stf.st_mode & S_IWOTH)) ?\
			ft_strjoin_free(CYAN, bt->name, 2) :\
			ft_strjoin_free(BK, bt->name, 2);
		((stf.st_mode & S_IWOTH) && (stf.st_mode & S_ISVTX)) ?\
			bt->name = ft_strjoin_free(GRN_S, bt->name, 2) : 0;
		((stf.st_mode & S_IWOTH) && !(stf.st_mode & S_ISVTX)) ?\
			bt->name = ft_strjoin_free(YLW_S, bt->name, 2) : 0;
	}
}

char			*ft_color(t_dash **btree)
{
	t_dash		*bt;
	struct stat	stf;

	bt = *btree;
	lstat(bt->path, &stf);
	if (S_ISREG(stf.st_mode) && ((S_IXUSR & stf.st_mode) ||\
		(S_IXGRP & stf.st_mode) || (S_IXOTH & stf.st_mode)))
		ft_color_dir_reg(btree, stf, 0);
	if (S_ISDIR(stf.st_mode))
		ft_color_dir_reg(btree, stf, 1);
	(S_ISLNK(stf.st_mode)) ? bt->name = ft_strjoin_free(MGTA, bt->name, 2) : 0;
	(S_ISFIFO(stf.st_mode)) ? bt->name = ft_strjoin_free(YLW, bt->name, 2) : 0;
	(S_ISSOCK(stf.st_mode)) ? bt->name = ft_strjoin_free(GRN, bt->name, 2) : 0;
	if (S_ISBLK(stf.st_mode) || S_ISCHR(stf.st_mode))
		bt->name = (S_ISBLK(stf.st_mode)) ? ft_strjoin_free(CYAN_BL_S,\
		bt->name, 2) : ft_strjoin_free(YLW_BL_S, bt->name, 2);
	bt->name = ft_strjoin_free(bt->name, RESET, 1);
	(bt->opt & 1024) ? ft_symbol_file(btree) : 0;
	return ((*btree)->name);
}

unsigned int	conv_sp(t_dash *bt, int *sp, int index)
{
	if (index == 0)
		return (sp[index] - ft_nbrlen(bt->physical_link));
	if (index == 1)
		return (sp[index] - ft_strlen(bt->own_name));
	if (index == 2)
		return (sp[index] - ft_strlen(bt->grp_name));
	if (index == 3)
		return (sp[index] - ft_nbrlen(bt->size));
	if (index == 4)
		return (sp[index] - ft_nbrlen((long)bt->inod));
	if (index == 5)
		return (sp[index] - ft_nbrlen((long)bt->majmin[0]));
	if (index == 6)
		return (sp[index] - ft_nbrlen((long)bt->majmin[1]));
	if (index == 7 && (bt->opt & 256))
		return ((sp[index] + 1) - (ft_strlen(bt->name) + sp[4]));
	if (index == 7 && !(bt->opt & 256))
		return (sp[index] - ft_strlen(bt->name));
	return (0);
}

static void		ft_insert_nbsp(t_dash **btree, int *sp, int len)
{
	t_dash		*tmp;

	tmp = *btree;
	if ((tmp->opt & 2))
	{
		if ((len = ft_nbrlen(tmp->physical_link)) >= sp[0])
			sp[0] = len;
		if ((len = ft_strlen(tmp->own_name)) >= sp[1])
			sp[1] = len;
		if ((len = ft_strlen(tmp->grp_name)) >= sp[2])
			sp[2] = len;
		if ((len = ft_nbrlen(tmp->size)) >= sp[3])
			sp[3] = len;
		if ((len = ft_nbrlen(tmp->majmin[0])) >= sp[5])
			sp[5] = len;
		if ((len = ft_nbrlen(tmp->majmin[1])) >= sp[6])
			sp[6] = len;
	}
	if ((len = ft_nbrlen(tmp->inod)) >= sp[4])
		sp[4] = len;
	if (!(tmp->opt & 256) && (len = ft_strlen(tmp->name)) >= sp[7])
		sp[7] = len;
	else if ((len = (ft_strlen(tmp->name) + ft_nbrlen(tmp->inod))) >= sp[7])
		sp[7] = len;
}

void			ft_how_many_sp(t_dash **btree, int *sp)
{
	t_dash		*tmp;

	tmp = *btree;
	ft_to_initialize(sp, 0);
	while (tmp)
	{
		ft_insert_nbsp(&tmp, sp, 0);
		tmp = tmp->next_file;
	}
}
