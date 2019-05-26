/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:45:07 by modaouch          #+#    #+#             */
/*   Updated: 2018/11/01 22:29:18 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_toexit(int bt, char *name)
{
	char	*name_returned;

	name_returned = NULL;
	if (bt == 1)
	{
		name_returned = ft_strjoin("ft_ls: ", name);
		perror(name_returned);
		free(name_returned);
		name_returned = NULL;
	}
	else
		exit(EXIT_FAILURE);
}

void		ft_bad_usage(t_info *info, char **av, int index)
{
	int		i;

	i = 1;
	while (!(info->opt & 64) && av[index][0] == '-' && av[index][i] &&\
		ft_strcmp(av[index], "--") && ft_strcmp(av[index], "-"))
	{
		if (!ft_strchr("alRrtGniSFdfC", av[index][i]))
		{
			ft_printf("ft_ls: illegal option -- %c\n", av[index][i]);
			write(1, "Usage : ls [-alRrtGniSFdfC] [file ...]\n", 39);
			ft_toexit(0, 0);
		}
		i++;
	}
}
