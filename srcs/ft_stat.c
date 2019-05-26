/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 14:24:14 by modaouch          #+#    #+#             */
/*   Updated: 2018/11/06 05:00:45 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_special_right(t_dash **element, t_info *fld)
{
	t_dash		*el;

	el = *element;
	((S_ISUID & fld->statfile.st_mode) && (S_IXUSR & fld->statfile.st_mode)) ?\
	el->type_chmod[3] = 's' : 0;
	((S_ISGID & fld->statfile.st_mode) && (S_IXGRP & fld->statfile.st_mode)) ?\
	el->type_chmod[6] = 's' : 0;
	((S_ISVTX & fld->statfile.st_mode) && (S_IXOTH & fld->statfile.st_mode)) ?\
	el->type_chmod[9] = 't' : 0;
	((S_ISUID & fld->statfile.st_mode) && !(S_IXUSR & fld->statfile.st_mode)) ?\
	el->type_chmod[3] = 'S' : 0;
	((S_ISGID & fld->statfile.st_mode) && !(S_IXGRP & fld->statfile.st_mode)) ?\
	el->type_chmod[6] = 'S' : 0;
	((S_ISVTX & fld->statfile.st_mode) && !(S_IXOTH & fld->statfile.st_mode)) ?\
	el->type_chmod[9] = 'T' : 0;
}

static void		ft_right(t_dash **element, t_info *info_folders)
{
	t_dash		*el;
	acl_t		acl;

	acl = NULL;
	el = *element;
	el->type_chmod[1] = (S_IRUSR & info_folders->statfile.st_mode) ? 'r' : '-';
	el->type_chmod[2] = (S_IWUSR & info_folders->statfile.st_mode) ? 'w' : '-';
	el->type_chmod[3] = (S_IXUSR & info_folders->statfile.st_mode) ? 'x' : '-';
	el->type_chmod[4] = (S_IRGRP & info_folders->statfile.st_mode) ? 'r' : '-';
	el->type_chmod[5] = (S_IWGRP & info_folders->statfile.st_mode) ? 'w' : '-';
	el->type_chmod[6] = (S_IXGRP & info_folders->statfile.st_mode) ? 'x' : '-';
	el->type_chmod[7] = (S_IROTH & info_folders->statfile.st_mode) ? 'r' : '-';
	el->type_chmod[8] = (S_IWOTH & info_folders->statfile.st_mode) ? 'w' : '-';
	el->type_chmod[9] = (S_IXOTH & info_folders->statfile.st_mode) ? 'x' : '-';
	if ((S_ISVTX & info_folders->statfile.st_mode) ||\
		((S_ISGID & info_folders->statfile.st_mode) ||\
		(S_ISUID & info_folders->statfile.st_mode)))
		ft_special_right(element, info_folders);
	el->type_chmod[10] =\
	((acl = acl_get_link_np(el->path, ACL_TYPE_EXTENDED))) ? '+' : ' ';
	if (listxattr(el->path, NULL, 0, XATTR_NOFOLLOW) > 0)
		el->type_chmod[10] = '@';
	(acl != NULL) ? acl_free((void *)acl) : 0;
}

void			ft_tomode(t_dash **element, t_info *info, char l)
{
	t_dash		*el;

	el = *element;
	lstat(el->path, &(info->statfile));
	ft_memset(el->type_chmod, '\0', 12);
	(S_ISDIR(info->statfile.st_mode)) ? el->type_chmod[0] = 'd' : 0;
	(S_ISREG(info->statfile.st_mode)) ? el->type_chmod[0] = '-' : 0;
	(S_ISCHR(info->statfile.st_mode)) ? el->type_chmod[0] = 'c' : 0;
	(S_ISBLK(info->statfile.st_mode)) ? el->type_chmod[0] = 'b' : 0;
	(S_ISLNK(info->statfile.st_mode)) ? el->type_chmod[0] = 'l' : 0;
	(S_ISFIFO(info->statfile.st_mode)) ? el->type_chmod[0] = 'p' : 0;
	(S_ISSOCK(info->statfile.st_mode)) ? el->type_chmod[0] = 's' : 0;
	if (l != 0 || el->opt & 32 || el->opt & 1024)
		ft_right(element, info);
	el->inod = (el->opt & 256) ? (long)info->statfile.st_ino : 0;
	if (el->opt & 1024 && !(el->opt & 32))
		ft_symbol_file(element);
}

void			ft_get_time(t_dash **element, t_info *info_folders)
{
	t_dash		*elem;
	char		*tea_time;
	char		**hour_year;
	int			i;

	i = 0;
	elem = *element;
	tea_time = (char *)ctime(&(info_folders->statfile.st_mtime));
	tea_time = tea_time + 4;
	(!(hour_year = ft_strsplit(&tea_time[7], ' '))) ? ft_toexit(0, 0) : 0;
	(ft_strncmp(hour_year[1], "10000", 5)) ? hour_year[1][4] = ' ' : 0;
	(!ft_strncmp(hour_year[1], "10000", 5)) ? hour_year[1][5] = '\0' : 0;
	tea_time[7] = '\0';
	ft_strcpy(elem->tea_time, tea_time);
	if ((time(0) - info_folders->statfile.st_mtime) >= 15778800 ||\
			info_folders->statfile.st_mtime > time(0))
		ft_strncat(elem->tea_time, hour_year[1], 5);
	else
		ft_strncat(elem->tea_time, hour_year[0], 5);
	elem->time_sec = info_folders->statfile.st_mtimespec.tv_sec;
	elem->time_nsec = (info_folders->statfile.st_mtimespec.tv_nsec);
	if (hour_year)
		ft_null_hour_year(hour_year);
}

void			ft_add_stat(t_dash **element, t_info *info_folders)
{
	t_dash		*elem;
	int			len;

	elem = *element;
	errno = 0;
	lstat(elem->path, &(info_folders->statfile));
	ft_tomode(&elem, info_folders, 1);
	if (!(elem->opt & 128) &&\
		(info_folders->perso_uid = getpwuid(info_folders->statfile.st_uid)))
		elem->own_name = ft_strdup(info_folders->perso_uid->pw_name);
	else
		elem->own_name = ft_itoa(info_folders->statfile.st_uid);
	if (!(elem->opt & 128) &&\
			(info_folders->grp = getgrgid(info_folders->statfile.st_gid)))
		elem->grp_name = ft_strdup(info_folders->grp->gr_name);
	else
		elem->grp_name = ft_itoa(info_folders->statfile.st_gid);
	elem->nb_block = info_folders->statfile.st_blocks;
	elem->physical_link = info_folders->statfile.st_nlink;
	if (elem->type_chmod[0] == 'l')
		((len = readlink(elem->path, elem->link, 255)) == -1) ? 0 :\
			(elem->link[len] = '\0');
	ft_size_major_minor(element, info_folders->statfile);
	ft_get_time(&elem, info_folders);
}
