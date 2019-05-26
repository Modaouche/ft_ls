/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_to_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 15:31:03 by modaouch          #+#    #+#             */
/*   Updated: 2018/11/02 00:30:40 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_quicksort(t_dash **root, t_dash **btree, int *not_first)
{
	t_dash	*pivot;
	t_dash	*tmp;
	t_dash	*right;
	t_dash	*left;
	t_dash	*save;

	tmp = *btree;
	pivot = *btree;
	right = NULL;
	left = NULL;
	while (pivot->next_file)
		pivot = pivot->next_file;
	while (tmp->next_file)
	{
		save = tmp->next_file;
		(ft_strcmp(tmp->name, pivot->name) <= 0) ?\
		ft_btree_push_front(&right, &tmp) : ft_btree_push_front(&left, &tmp);
		tmp = save;
	}
	if (left)
		ft_quicksort(root, &left, not_first);
	((*not_first)++ == 0) ? *root = NULL : 0;
	ft_btree_push_front(root, &pivot);
	if (right)
		ft_quicksort(root, &right, not_first);
}

void		ft_rev_quicksort(t_dash **root, t_dash **btree, int *not_first)
{
	t_dash	*pivot;
	t_dash	*tmp;
	t_dash	*right;
	t_dash	*left;
	t_dash	*save;

	tmp = *btree;
	pivot = *btree;
	right = NULL;
	left = NULL;
	while (pivot->next_file)
		pivot = pivot->next_file;
	while (tmp->next_file)
	{
		save = tmp->next_file;
		(ft_strcmp(tmp->name, pivot->name) > 0) ?\
		ft_btree_push_front(&right, &tmp) : ft_btree_push_front(&left, &tmp);
		tmp = save;
	}
	if (left)
		ft_rev_quicksort(root, &left, not_first);
	((*not_first)++ == 0) ? *root = NULL : 0;
	ft_btree_push_front(root, &pivot);
	if (right)
		ft_rev_quicksort(root, &right, not_first);
}

static int	ft_swap_time(t_dash *tmp, t_dash *pvt, char *strtp, char *strpv)
{
	if (!(tmp->opt & 8))
	{
		if (tmp->time_sec > pvt->time_sec)
			return (1);
		if (tmp->time_sec == pvt->time_sec)
			if (tmp->time_nsec >= pvt->time_nsec)
				if (ft_strcmp(strtp, strpv) < 0)
					return (1);
	}
	else
	{
		if (tmp->time_sec < pvt->time_sec)
			return (1);
		if (tmp->time_sec == pvt->time_sec)
			if (tmp->time_nsec <= pvt->time_nsec)
				if (ft_strcmp(strtp, strpv) > 0)
					return (1);
	}
	return (0);
}

void		ft_time_quicksort(t_dash **root, t_dash **btree, int *not_first)
{
	t_dash	*pivot;
	t_dash	*tmp;
	t_dash	*right;
	t_dash	*left;
	t_dash	*save;

	tmp = *btree;
	pivot = *btree;
	right = NULL;
	left = NULL;
	while (pivot->next_file)
		pivot = pivot->next_file;
	while (tmp->next_file)
	{
		save = tmp->next_file;
		(ft_swap_time(tmp, pivot, tmp->name, pivot->name)) ?\
		ft_btree_push_front(&right, &tmp) : ft_btree_push_front(&left, &tmp);
		tmp = save;
	}
	if (left)
		ft_time_quicksort(root, &left, not_first);
	((*not_first)++ == 0) ? *root = NULL : 0;
	ft_btree_push_front(root, &pivot);
	if (right)
		ft_time_quicksort(root, &right, not_first);
}

void		ft_rev_time_quicksort(t_dash **root, t_dash **btree,\
			int *not_first)
{
	t_dash	*pivot;
	t_dash	*tmp;
	t_dash	*right;
	t_dash	*left;
	t_dash	*save;

	tmp = *btree;
	pivot = *btree;
	right = NULL;
	left = NULL;
	while (pivot->next_file)
		pivot = pivot->next_file;
	while (tmp->next_file)
	{
		save = tmp->next_file;
		(ft_swap_time(tmp, pivot, tmp->name, pivot->name)) ?\
		ft_btree_push_front(&right, &tmp) : ft_btree_push_front(&left, &tmp);
		tmp = save;
	}
	if (left)
		ft_rev_time_quicksort(root, &left, not_first);
	((*not_first)++ == 0) ? *root = NULL : 0;
	ft_btree_push_front(root, &pivot);
	if (right)
		ft_rev_time_quicksort(root, &right, not_first);
}
