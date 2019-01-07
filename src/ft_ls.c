/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 18:41:04 by tblaudez          #+#    #+#             */
/*   Updated: 2018/07/17 18:42:42 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			arg_is_dir(t_ls *list, t_info *infos, t_ls **head)
{
	char	*tmp_path;
	t_ls	*first;

	first = list;
	while (!T_HIDD && infos->cur_file && infos->cur_file->d_name[0] == '.')
		infos->cur_file = readdir(infos->cur_dir);
	if (!infos->cur_file && (list->is_dir_empty = true))
		ft_printf("\n%s:\n", infos->path);
	while (infos->cur_file)
	{
		tmp_path = create_path(infos->path, infos->cur_file->d_name);
		(T_LIST || T_REC ? lstat : stat)(tmp_path, infos->file_stat);
		copy_infos(list, infos, infos->cur_file->d_name);
		free(tmp_path);
		if ((infos->cur_file = readdir(infos->cur_dir)) \
		&& (list->next = create_list()))
			list = list->next;
	}
	merge_sort(&first, infos->flag);
	(T_LIST ? print_list(first, infos->flag) \
	: print_normal(first, infos->flag));
	if (T_REC)
		recursive_arg_is_dir((*head = first), infos);
	free_infos(infos);
	return (1);
}

int			init_struct(t_ls *list, char *path, char flag, t_ls **head)
{
	t_info		*infos;
	int			stat_ret;

	if (!(infos = (t_info *)malloc(sizeof(t_info))) \
	|| !(infos->file_stat = (struct stat *)malloc(sizeof(struct stat))))
		exit(EXIT_FAILURE);
	stat_ret = (LIST ? lstat : stat)(path, infos->file_stat);
	infos->path = ft_strdup(path);
	infos->flag = flag;
	infos->cur_dir = NULL;
	infos->cur_file = NULL;
	if (!IS_A_DIR(infos->file_stat->st_mode) && !stat_ret)
	{
		arg_is_file(list, infos);
		free_infos(infos);
		return (0);
	}
	if (!(infos->cur_dir = opendir(path)) \
	|| !(infos->cur_file = readdir(infos->cur_dir)))
	{
		print_error(path, stat_ret, flag);
		free_infos(infos);
		return (0);
	}
	return (arg_is_dir(list, infos, &list) && (*head = list));
}

void		arg_is_file(t_ls *list, t_info *infos)
{
	int i;

	if (IS_A_FILE(infos->file_stat->st_mode))
		i = ft_charrsrc(infos->path, '/') + 1;
	else
		i = 0;
	copy_infos(list, infos, infos->path + i);
	if (!T_LIST)
		print_name_color(list, infos->flag);
	else
		print_long_format(list, infos->flag);
}

static int	recursive_loop(char **argv, char flag)
{
	t_ls	*list;

	while (*argv)
	{
		if (!(list = create_list()))
			return (EXIT_FAILURE);
		init_struct(list, *argv, flag, &list);
		free_list(list);
		argv++;
	}
	return (1);
}

int			main(int argc, char **argv)
{
	t_ls		*list;
	char		flag;
	int			i;

	flag = 0;
	i = check_flag_ls(&flag, argv + 1);
	argv += i;
	if (argc - i <= 1)
	{
		if (!(list = create_list()))
			return (EXIT_FAILURE);
		i = init_struct(list, *argv ? *argv : "./", flag, &list);
		free_list(list);
	}
	else
		i = recursive_loop(argv, flag);
	return (!i ? EXIT_FAILURE : EXIT_SUCCESS);
}
