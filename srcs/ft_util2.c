/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 11:25:49 by modaouch          #+#    #+#             */
/*   Updated: 2018/11/02 07:48:47 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_total(t_dash *tmp)
{
	int		total;
	int		point_detector;

	total = 0;
	point_detector = 0;
	if (tmp->opt & 2)
	{
		while (tmp)
		{
			if (ft_hidden_face(tmp))
			{
				point_detector++;
				total = total + tmp->nb_block;
			}
			tmp = tmp->next_file;
		}
		if (point_detector)
			ft_printf("total %d\n", total);
	}
}

int			ft_hidden_face(t_dash *tmp)
{
	if (!tmp)
		return (-1);
	if ((tmp->opt & 1) || (!(tmp->opt & 1) && tmp->name[0] != '.'))
		return (1);
	else
		return (0);
}

int			ft_wave_len(t_dash *btree)
{
	t_dash	*tmp;
	int		i;

	i = 0;
	tmp = btree;
	while (tmp && tmp->type_chmod[0])
	{
		i++;
		tmp = tmp->next_file;
	}
	return (i);
}

int			ft_wave_len_hidden(t_dash *btree)
{
	int		count;

	count = 0;
	while (btree && !(btree->opt & 2048))
	{
		if (ft_hidden_face(btree))
			count++;
		btree = btree->next_file;
	}
	return (count);
}

void		ft_to_initialize(int *sp, t_dash **elem)
{
	if (sp)
	{
		sp[0] = 0;
		sp[1] = 0;
		sp[2] = 0;
		sp[3] = 1;
		sp[4] = 0;
		sp[5] = 0;
		sp[6] = 0;
		sp[7] = 0;
	}
	if (elem && *elem)
	{
		(*elem)->inod = 0;
		ft_bzero((*elem)->link, 256);
		ft_bzero((*elem)->tea_time, 40);
		(*elem)->to_open = NULL;
		(*elem)->own_name = NULL;
		(*elem)->grp_name = NULL;
		(*elem)->physical_link = 0;
		(*elem)->size = 0;
		(*elem)->next_file = NULL;
		(*elem)->next_level = NULL;
	}
}
