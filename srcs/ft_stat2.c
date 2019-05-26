/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stat2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 19:33:36 by modaouch          #+#    #+#             */
/*   Updated: 2018/11/02 00:29:16 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_size_major_minor(t_dash **element, struct stat statfile)
{
	t_dash	*el;

	el = *element;
	el->majmin[0] = 0;
	el->majmin[1] = 0;
	if (el->type_chmod[0] == 'c' || el->type_chmod[0] == 'b')
	{
		el->majmin[0] = major(statfile.st_rdev);
		el->majmin[1] = minor(statfile.st_rdev);
	}
	else
		el->size = statfile.st_size;
}

void		ft_add_slash(t_dash **elem, char *name, char *path_root, char btn)
{
	t_dash	*element;
	int		end;

	end = 0;
	element = *elem;
	if (btn == 1)
		element->path = ft_strdup(name);
	else
	{
		end = ft_strlen(path_root);
		if (path_root[end - 1] != '/' || ft_strcmp(path_root, "/"))
		{
			(!(element->path = ft_strjoin_free(path_root, "/", 0))) ?\
				ft_toexit(0, 0) : 0;
			(!(element->path = ft_strjoin_free(element->path, name, 1))) ?\
				ft_toexit(0, 0) : 0;
		}
		else
			(!(element->path = ft_strjoin_free(path_root, name, 0))) ?\
				ft_toexit(0, 0) : 0;
	}
}

void		ft_null_hour_year(char **hour_year)
{
	ft_bzero(hour_year[0], 5);
	free(hour_year[0]);
	ft_bzero(hour_year[1], 5);
	free(hour_year[1]);
	free(hour_year);
	hour_year = NULL;
}
