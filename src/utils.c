/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 18:41:51 by tblaudez          #+#    #+#             */
/*   Updated: 2018/07/24 18:41:53 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		check_flag_ls(char *flag, char **argv)
{
	int i;
	int j;
	int k;

	i = -1;
	while (argv[++i] && argv[i][0] == '-' && (j = 1))
		while (argv[i][j])
		{
			if ((k = ft_charsrc("lRart", argv[i][j])) >= 0)
				*flag |= 1 << (4 - k);
			else
			{
				ft_putstr_fd("ls : illegal option -- ", 2);
				ft_putendl_fd(&argv[i][j], 2);
				exit(EXIT_FAILURE);
			}
			j++;
		}
	return (i + 1);
}

int		is_valid_dir(t_ls *list, t_info *infos)
{
	if (list->rights[0] != 'd' || (!T_HIDD \
	&& (list->d_name)[0] == '.') || !ft_strcmp(list->d_name, ".") \
	|| !ft_strcmp(list->d_name, ".."))
		return (0);
	return (1);
}

char	*create_path(char *path, char *name)
{
	char *ret;

	ret = ft_strnew(ft_strlen(path) + ft_strlen(name) + 1);
	ft_strcpy(ret, path);
	if (ret[ft_strlen(ret) - 1] != '/')
		ft_strcat(ret, "/");
	if (ft_strlen(name) && !ft_strequ(name, "."))
		ft_strcat(ret, name);
	return (ret);
}

t_ls	*create_list(void)
{
	t_ls	*list;

	if (!(list = (t_ls *)malloc(sizeof(t_ls))))
		exit(EXIT_FAILURE);
	list->is_dir_empty = false;
	list->rights = NULL;
	list->st_nlink = 0;
	list->pw_name = NULL;
	list->gr_name = NULL;
	list->st_size = 0;
	list->blk_size = 0;
	list->modif_time = 0;
	list->d_name = NULL;
	list->path = NULL;
	list->is_dir = NULL;
	list->next = NULL;
	return (list);
}

void	recursive_arg_is_dir(t_ls *list, t_info *infos)
{
	char	*tmp_path;

	while (list)
	{
		if (list->is_dir_empty == false && is_valid_dir(list, infos))
		{
			list->is_dir = create_list();
			tmp_path = create_path(list->path, list->d_name);
			if (!init_struct(list->is_dir, tmp_path, infos->flag, \
			&(list->is_dir)))
			{
				free_list(list->is_dir);
				list->is_dir = NULL;
			}
			free(tmp_path);
		}
		list = list->next;
	}
}
