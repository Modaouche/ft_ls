/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 13:36:57 by modaouch          #+#    #+#             */
/*   Updated: 2018/11/06 02:54:51 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_opt.h"

int					ft_link_to_doss(t_dash *tmp)
{
	DIR				*opened_link;

	errno = 0;
	if (tmp->type_chmod[0] == 'l')
	{
		if ((opened_link = opendir(tmp->path)))
		{
			(!closedir(opened_link)) ? 0 : ft_toexit(1, tmp->path);
			return (1);
		}
		if (errno != ENOTDIR)
			return (1);
	}
	return (0);
}

int					ft_nb_elem(t_dash *btree, int *nbfile)
{
	struct dirent	*dirent_tmp;
	DIR				*to_open_tmp;
	int				nb_elem;

	nb_elem = 0;
	errno = 0;
	if (!(to_open_tmp = opendir(btree->path)))
	{
		if (errno == EACCES)
		{
			if (nbfile[0] && ft_hidden_face(btree))
				ft_printf("\n%s:\n", btree->path);
			else if (nbfile[1] > 1 && ft_hidden_face(btree))
				ft_printf("%s:\n", btree->path);
			ft_toexit(1, btree->name);
		}
	}
	else
	{
		while ((dirent_tmp = readdir(to_open_tmp)))
			nb_elem++;
		if ((closedir(to_open_tmp) == -1))
			ft_toexit(1, btree->name);
	}
	return (nb_elem);
}

void				ft_free_name_folders(t_info *info_folders)
{
	int				i;

	i = 0;
	if ((info_folders->name))
	{
		while (info_folders->name[i])
		{
			ft_strdel(&info_folders->name[i]);
			i++;
		}
		free(info_folders->name);
		info_folders->name = 0;
	}
}

static int			ft_n_opt(const char *av)
{
	int				n;

	n = 0;
	while (g_opt_tab[n].letter)
	{
		if (!ft_strncmp(g_opt_tab[n].letter, av,\
			ft_strlen(g_opt_tab[n].letter)))
			return (n);
		n++;
	}
	return (-1);
}

void				ft_opt(t_info *info, char **av, int index)
{
	int				i;
	int				num_opt;

	i = 1;
	ft_bad_usage(info, av, index);
	while (av[index][i] && !(info->opt & 64) && av[index][0] == '-')
	{
		num_opt = ft_n_opt(&av[index][i]);
		(num_opt > -1) ? g_opt_tab[num_opt].get_option(&info->opt) : 0;
		if (!ft_strcmp(av[index], "--") && !(info->opt & 64))
			info->opt += 64;
		i++;
	}
	(av[index][0] != '-' && !(info->opt & 64)) ? info->opt += 64 : 0;
}
