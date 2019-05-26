/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 16:19:53 by modaouch          #+#    #+#             */
/*   Updated: 2018/11/06 04:14:47 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_ini(char *name, char *bug, int *j, t_info *info_fold)
{
	if (j)
		*j = 1;
	if (bug)
		*bug = 1;
	if (name && info_fold)
		ft_toexit(1, name);
}

static int		ft_check_valid(char *av, char *bug, int *j, t_info *info_fld)
{
	struct stat	tmp;

	if (lstat(av, &tmp) == -1)
	{
		ft_ini(av, bug, j, info_fld);
		return (0);
	}
	return (1);
}

static int		ft_parse_nb_elem(char **av, char bug, int ac, t_info *info_fld)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (av[++i])
	{
		if (j || ac || bug || (av[i][0] != '-' || !ft_strcmp(av[i], "-")))
		{
			if (!ft_check_valid(av[i], &bug, &j, info_fld))
				continue ;
			(info_fld) ? info_fld->name[ac] = ft_strdup(av[i]) : 0;
			ac++;
			continue ;
		}
		if ((!ft_strcmp(av[i], "--") && j == 0 && !ac))
		{
			ft_ini(0, 0, &j, 0);
			continue ;
		}
		(info_fld && !(info_fld->opt & 64)) ? ft_opt(info_fld, av, i) : 0;
	}
	(ac == 0 && bug == 0 && info_fld) ? info_fld->name[0] = ft_strdup(".") : 0;
	ac = (bug == 1 && ac == 0) ? -1 : ac;
	return ((ac == 0) ? 1 : ac);
}

int				main(int ac, char **av)
{
	t_dash		*btree;
	t_info		info_folders;

	info_folders.opt = 0;
	btree = 0;
	ac = ft_parse_nb_elem(av, 0, 0, 0);
	ac = (ac == -1) ? 0 : ac;
	if (!(info_folders.name = (char **)malloc(sizeof(char *) * (ac + 1))))
		ft_toexit(0, 0);
	info_folders.name[ac] = 0;
	if (ft_parse_nb_elem(av, 0, 0, &info_folders) == -1)
	{
		ft_free_name_folders(&info_folders);
		ft_toexit(0, 0);
	}
	ft_ls(&btree, &info_folders);
	ft_free_name_folders(&info_folders);
	return (0);
}
