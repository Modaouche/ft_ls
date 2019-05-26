/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 14:17:22 by modaouch          #+#    #+#             */
/*   Updated: 2018/11/06 05:09:49 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"
# include "libft/ft_printf/includes/ft_printf.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <time.h>
# include <grp.h>
# include <pwd.h>
# include <errno.h>
# include <dirent.h>
# include <sys/ioctl.h>
# define BK			"\033[30m"
# define RED		"\033[31m"
# define GRN		"\033[32m"
# define YLW		"\033[33m"
# define BLUE		"\033[34m"
# define MGTA		"\033[35m"
# define CYAN		"\033[36m"
# define RED_S		"\033[41m"
# define GRN_S		"\033[42m"
# define YLW_S		"\033[43m"
# define BLUE_S		"\033[44m"
# define CYAN_S		"\033[46m"
# define YLW_BL_S	"\033[43m\033[34m"
# define CYAN_BL_S	"\033[46m\033[34m"
# define RESET		"\033[0m"

typedef struct		s_info
{
	struct stat		statfile;
	struct group	*grp;
	struct dirent	*infodirent;
	struct passwd	*perso_uid;
	char			**name;
	char			*path_root;
	int				opt;
}					t_info;

typedef struct		s_dash
{
	DIR				*to_open;
	char			*path;
	char			*name;
	ino_t			inod;
	char			link[256];
	char			type_chmod[12];
	char			*own_name;
	char			*grp_name;
	char			tea_time[40];
	unsigned int	physical_link;
	unsigned int	size;
	unsigned int	nb_block;
	time_t			time_sec;
	long			time_nsec;
	int				opt;
	unsigned int	majmin[2];
	struct s_dash	*next_level;
	struct s_dash	*next_file;
}					t_dash;

typedef struct		s_opt
{
	char			*letter;
	void			(*get_option)(int *opt);
}					t_opt;

void				ft_opt(t_info *info, char **av, int index);
void				ft_toexit(int bt, char *name);
void				ft_bad_usage(t_info *info, char **av, int index);
void				ft_ls(t_dash **btree, t_info *info_folders);
void				ft_recursive_fill_it(t_dash **btree, t_info *info_folders,\
					int *nbfile, int first);
void				ft_simple_fill_it(t_dash **btree, t_info *info_folders,\
					int *nbfile);
t_dash				*ft_btree_new(t_info *info_folders, int nbr, char btn);
void				ft_insert_wave(t_dash **btree,\
					t_info *info_folders, char btn);
void				ft_btree_push_front(t_dash **btree, t_dash **to_add);
void				ft_to_initialize(int *sp, t_dash **elem);
int					ft_wave_len(t_dash *btree);
int					ft_wave_len_hidden(t_dash *btree);
int					ft_nb_elem(t_dash *btree, int *nbfile);
int					ft_nbfile(t_dash *btree);
int					ft_nbfold(t_dash *btree);
void				ft_add_stat(t_dash **elem, t_info *info_folders);
void				ft_add_slash(t_dash **elem, char *name,\
					char *path_root, char btn);
void				ft_remove_slash(t_dash **elem, char *name);
void				ft_tomode(t_dash **element, t_info *info_folders, char l);
int					ft_cycle(t_dash *tmp);
int					ft_hidden_face(t_dash *tmp);
int					ft_link_to_doss(t_dash *tmp);
void				ft_get_time(t_dash **element, t_info *info_folders);
void				ft_size_major_minor(t_dash **element,\
					struct stat statfile);
void				ft_null_hour_year(char **hour_year);
void				ft_how_many_sp(t_dash **btree, int *sp);
unsigned int		conv_sp(t_dash *bt, int *sp, int index);
int					ft_nbrlen(long nbr);
t_dash				*ft_init_column_var(t_dash **print_btree, int *sp,\
					int *off_col, int *count);
int					ft_next_line(t_dash **btree, t_dash **tmp,\
					int *count, int *i);
int					ft_next_column(t_dash **bt, t_dash **tmp,\
					int count, int *off_col);
t_dash				**ft_offset(t_dash **bt, int offset);
t_dash				**ft_offset_hidden(t_dash **bt, int offset);
int					ft_get_offset(t_dash *bt, int columns);
int					ft_get_offset_hidden(t_dash *bt, int column);
int					ft_nbcolumn(int *sp);
char				*ft_color(t_dash **btree);
void				ft_symbol_file(t_dash **element);
void				ft_btree_add_file(t_dash **btree, t_info *info_folders,\
					int nbr, char btn);
void				ft_btree_add_level(t_dash **btree, t_dash *neww);
void				ft_sorting_choice(t_dash **btree, int *not_first);
void				ft_quicksort(t_dash **root, t_dash **btree,\
					int *not_first);
void				ft_rev_quicksort(t_dash **root, t_dash **btree,\
					int *not_first);
void				ft_time_quicksort(t_dash **root, t_dash **btree,\
					int *not_first);
void				ft_rev_time_quicksort(t_dash **root, t_dash **btree,\
					int *not_first);
void				ft_size_quicksort(t_dash **root, t_dash **btree,\
					int *not_first);
void				ft_rev_size_quicksort(t_dash **root, t_dash **btree,\
					int *not_first);
void				ft_free_name_folders(t_info *info_folders);
void				ft_btreedel(t_dash **btree);
void				ft_total(t_dash *tmp);
void				ft_print_path(t_dash *tmp, int *nbfile, int *i, int btn);
void				ft_print(t_dash **btree, int *sp, int btn);
void				ft_column(t_dash **print_btree, t_dash *bt, int *sp, int i);
void				ft_column_file(t_dash **print_btree, t_dash *bt,\
					int *sp, int i);
void				ft_opt_hidden(int *opt);
void				ft_opt_long(int *opt);
void				ft_opt_recursive(int *opt);
void				ft_opt_reverse(int *opt);
void				ft_opt_time(int *opt);
void				ft_opt_color(int *opt);
void				ft_opt_num_info(int *opt);
void				ft_opt_inode(int *opt);
void				ft_opt_size(int *opt);
void				ft_opt_symbol(int *opt);
void				ft_opt_curr_dir(int *opt);
void				ft_opt_unsorted(int *opt);
void				ft_opt_column(int *opt);
#endif
