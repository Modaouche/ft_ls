/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_to_sort2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:17:11 by modaouch          #+#    #+#             */
/*   Updated: 2018/11/02 00:31:38 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ft_swap_size(t_dash *tmp, t_dash *pvt)
{
	if (!(tmp->opt & 8))
	{
		if (tmp->size > pvt->size)
			return (1);
		if (tmp->size == pvt->size)
			if (ft_strcmp(tmp->name, pvt->name) < 0)
				return (1);
	}
	else
	{
		if (tmp->size < pvt->size)
			return (1);
		if (tmp->size == pvt->size)
			if (ft_strcmp(tmp->name, pvt->name) > 0)
				return (1);
	}
	return (0);
}

static void	ft_list_reverse(t_dash **begin_list)
{
	t_dash	*prev;
	t_dash	*next;
	t_dash	*curr;

	prev = 0;
	curr = *begin_list;
	while (curr)
	{
		next = curr->next_file;
		curr->next_file = prev;
		prev = curr;
		curr = next;
	}
	*begin_list = prev;
}

void		ft_size_quicksort(t_dash **root, t_dash **btree, int *not_first)
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
		(ft_swap_size(tmp, pivot) == 1) ?\
		ft_btree_push_front(&right, &tmp) : ft_btree_push_front(&left, &tmp);
		tmp = save;
	}
	if (left)
		ft_size_quicksort(root, &left, not_first);
	((*not_first)++ == 0) ? *root = NULL : 0;
	ft_btree_push_front(root, &pivot);
	if (right)
		ft_size_quicksort(root, &right, not_first);
}

void		ft_rev_size_quicksort(t_dash **root, t_dash **btree,\
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
		(ft_swap_size(tmp, pivot) == 1) ?\
		ft_btree_push_front(&right, &tmp) : ft_btree_push_front(&left, &tmp);
		tmp = save;
	}
	if (left)
		ft_rev_size_quicksort(root, &left, not_first);
	((*not_first)++ == 0) ? *root = NULL : 0;
	ft_btree_push_front(root, &pivot);
	if (right)
		ft_rev_size_quicksort(root, &right, not_first);
}

void		ft_sorting_choice(t_dash **btree, int *not_first)
{
	t_dash	*tmp;

	tmp = *btree;
	if (!(tmp->opt & 4096))
	{
		if (!(tmp->opt & 16) && !(tmp->opt & 8) && !(tmp->opt & 512))
			ft_quicksort(btree, btree, not_first);
		else if (!(tmp->opt & 16) && (tmp->opt & 8) && !(tmp->opt & 512))
			ft_rev_quicksort(btree, btree, not_first);
		else if ((tmp->opt & 16) && !(tmp->opt & 8) && !(tmp->opt & 512))
			ft_time_quicksort(btree, btree, not_first);
		else if ((tmp->opt & 16) && (tmp->opt & 8) && !(tmp->opt & 512))
			ft_rev_time_quicksort(btree, btree, not_first);
		else if ((tmp->opt & 512) && !(tmp->opt & 16) && !(tmp->opt & 8))
			ft_size_quicksort(btree, btree, not_first);
		else if ((tmp->opt & 512) && !(tmp->opt & 16) && (tmp->opt & 8))
			ft_rev_size_quicksort(btree, btree, not_first);
	}
	else
		ft_list_reverse(btree);
}
