/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 18:41:42 by tblaudez          #+#    #+#             */
/*   Updated: 2018/07/24 18:41:43 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_normal(t_ls *list, char flag)
{
	static int	call_nbr = 0;
	t_ls		*first;

	first = list;
	if (call_nbr && list->is_dir_empty == false)
		ft_printf("\n%s:\n", list->path);
	while (list)
	{
		if (list->is_dir_empty == false)
			print_name_color(list, flag);
		list = list->next;
	}
	call_nbr++;
}

void		print_name_color(t_ls *list, char flag)
{
	if (list->rights[0] == 'd')
	{
		if (ft_charnsrc(list->rights, '-', 10) >= 0)
			ft_printf("{bold}{cyan}%s{eoc}", list->d_name);
		else
			ft_printf("{reverse}{cyan}%s{eoc}", list->d_name);
	}
	else if (list->rights[0] == 'l')
	{
		ft_printf("{magenta}%s{eoc}", list->d_name);
		if (LIST)
			ft_printf(" -> %s", list->rights + 10);
	}
	else if (list->rights[3] == 'x')
		ft_printf("{red}%s{eoc}", list->d_name);
	else
		ft_putstr(list->d_name);
	ft_putchar('\n');
}

static void	print_detail(t_ls *list)
{
	ft_printf("%.10s  %3d ", list->rights, list->st_nlink);
	ft_printf("%8s  %12s", list->pw_name, list->gr_name);
	ft_printf(" %6d ", list->st_size);
}

void		print_long_format(t_ls *list, char flag)
{
	print_detail(list);
	if (time(NULL) - list->modif_time < 16070400)
		ft_printf("%.12s ", ctime(&list->modif_time) + 4);
	else
		ft_printf("%.6s %.4s ", ctime(&list->modif_time) + 4, \
		ctime(&list->modif_time) + 20);
	print_name_color(list, flag);
}

void		print_list(t_ls *list, char flag)
{
	t_ls		*first;
	static int	call_nbr = 0;

	first = list;
	if (call_nbr && list->is_dir_empty == false)
		ft_printf("\n%s:\n", list->path);
	if (list->is_dir_empty == false)
		ft_printf("total %U\n", search_total(list));
	while (list && list->is_dir_empty == false)
	{
		print_long_format(list, flag);
		list = list->next;
	}
	call_nbr++;
}
