/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 00:26:40 by tblaudez          #+#    #+#             */
/*   Updated: 2018/07/01 00:26:43 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <stdbool.h>
# include "libft.h"
# include "ft_printf.h"

# define LIST (flag & (1 << 4))
# define REC (flag & (1 << 3))
# define HIDD (flag & (1 << 2))
# define REV (flag & (1 << 1))
# define MTIME (flag & 1)

# define P_LIST (*flag & (1 << 4))

# define T_LIST (infos->flag & (1 << 4))
# define T_REC (infos->flag & (1 << 3))
# define T_HIDD (infos->flag & (1 << 2))
# define T_REV (infos->flag & (1 << 1))
# define T_MTIME (infos->flag & 1)

# define IS_A_DIR(mode) ((mode & S_IFMT) == S_IFDIR)
# define IS_A_LNK(mode) ((mode & S_IFMT) == S_IFLNK)
# define IS_A_FILE(mode) (!IS_A_DIR(mode) && !IS_A_LNK(mode))

typedef struct	s_ls
{
	bool			is_dir_empty;
	char			*rights;
	nlink_t			st_nlink;
	char			*pw_name;
	char			*gr_name;
	off_t			st_size;
	blkcnt_t		blk_size;
	__darwin_time_t	modif_time;
	char			*d_name;
	char			*path;
	struct s_ls		*is_dir;
	struct s_ls		*next;
}				t_ls;

typedef struct	s_info
{
	DIR				*cur_dir;
	struct dirent	*cur_file;
	struct stat		*file_stat;
	char			*path;
	char			flag;
}				t_info;

void			print_list(t_ls *list, char flag);
int				init_struct(t_ls *list, char *path, char flag, t_ls **head);
int				arg_is_dir(t_ls *list, t_info *infos, t_ls **head);
void			arg_is_file(t_ls *list, t_info *infos);
void			print_normal(t_ls *list, char flag);
int				search_total(t_ls *list);
void			print_error(char *path, int stat_ret, char flag);
void			print_name_color(t_ls *list, char flag);
char			*create_path(char *path, char *name);
void			copy_infos(t_ls *list, t_info *infos, char *d_name);
int				is_valid_dir(t_ls *list, t_info *infos);
t_ls			*create_list(void);
void			print_long_format(t_ls *list, char flag);
int				check_flag_ls(char *flag, char **argv);
void			free_infos(t_info *infos);
int				free_list(t_ls *list);
void			merge_sort(t_ls **head_ref, char flag);
void			merge_sort_ascii(t_ls **head_ref, char flag);
void			merge_sort_time(t_ls **head_ref, char flag);
void			merge_sort_reverse(t_ls **head_ref);
t_ls			*sorted_merge_reverse(t_ls *a, t_ls *b);
void			front_back_split(t_ls *source, t_ls **front_ref,
				t_ls **back_ref);
void			recursive_arg_is_dir(t_ls *list, t_info *infos);

#endif
