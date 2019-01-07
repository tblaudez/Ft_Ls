/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 18:44:21 by tblaudez          #+#    #+#             */
/*   Updated: 2018/07/24 18:44:23 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		create_name(t_info *infos, char (*link)[1024], char *d_name)
{
	if (infos->cur_file)
	{
		ft_strncpy(*link, infos->path, sizeof(*link));
		if (!ft_strequ(infos->path, "/"))
			ft_strncat(*link, "/", sizeof(*link));
		ft_strncat(*link, infos->cur_file->d_name, sizeof(*link));
	}
	else
		ft_strncpy(*link, d_name, sizeof(*link));
}

int			search_total(t_ls *list)
{
	blkcnt_t	ret;

	ret = 0;
	while (list)
	{
		ret += list->blk_size;
		list = list->next;
	}
	return (ret);
}

void		print_error(char *path, int stat_ret, char flag)
{
	if (!stat_ret && REC)
		ft_printf("\n%s:\n", path);
	ft_putstr_fd("ls: ", 2);
	perror(path + ft_charrsrc(path, '/') + 1);
}

static void	add_rights(struct stat *stats, t_ls *list, t_info *infos,
char *d_name)
{
	char	link[1024];
	ssize_t	link_size;

	list->rights = ft_strnew(10);
	link_size = 0;
	ft_strcat(list->rights, IS_A_DIR(stats->st_mode) ? "d" : "-");
	ft_strcat(list->rights, ((stats->st_mode & S_IRUSR) ? "r" : "-"));
	ft_strcat(list->rights, ((stats->st_mode & S_IWUSR) ? "w" : "-"));
	ft_strcat(list->rights, ((stats->st_mode & S_IXUSR) ? "x" : "-"));
	ft_strcat(list->rights, ((stats->st_mode & S_IRGRP) ? "r" : "-"));
	ft_strcat(list->rights, ((stats->st_mode & S_IWGRP) ? "w" : "-"));
	ft_strcat(list->rights, ((stats->st_mode & S_IXGRP) ? "x" : "-"));
	ft_strcat(list->rights, ((stats->st_mode & S_IROTH) ? "r" : "-"));
	ft_strcat(list->rights, ((stats->st_mode & S_IWOTH) ? "w" : "-"));
	ft_strcat(list->rights, ((stats->st_mode & S_IXOTH) ? "x" : "-"));
	if (IS_A_LNK(stats->st_mode))
	{
		list->rights[0] = 'l';
		create_name(infos, &link, d_name);
		if ((link_size = readlink(link, link, sizeof(link) - 1)) != -1)
		{
			link[link_size] = '\0';
			list->rights = ft_strjoinfree(list->rights, link, 1, 0);
		}
	}
}

void		copy_infos(t_ls *list, t_info *infos, char *d_name)
{
	struct passwd *uid;

	uid = getpwuid(infos->file_stat->st_uid);
	list->pw_name = ft_strdup((uid ? uid->pw_name \
	: ft_itoa(infos->file_stat->st_uid)));
	list->gr_name = ft_strdup(getgrgid(infos->file_stat->st_gid)->gr_name);
	list->d_name = ft_strdup(d_name);
	list->path = ft_strdup(infos->path);
	add_rights(infos->file_stat, list, infos, d_name);
	list->st_nlink = infos->file_stat->st_nlink;
	list->st_size = infos->file_stat->st_size;
	list->blk_size = infos->file_stat->st_blocks;
	list->modif_time = infos->file_stat->st_mtime;
	if (!list->pw_name || !list->gr_name || !list->d_name || !list->path)
		exit(EXIT_FAILURE);
}
