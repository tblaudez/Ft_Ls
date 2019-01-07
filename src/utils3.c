/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 19:36:28 by tblaudez          #+#    #+#             */
/*   Updated: 2018/07/24 19:36:30 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_infos(t_info *infos)
{
	if (infos->cur_dir)
		closedir(infos->cur_dir);
	free(infos->cur_file);
	free(infos->file_stat);
	free(infos->path);
	free(infos);
}

int		free_list(t_ls *list)
{
	t_ls *tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->path);
		free(tmp->rights);
		free(tmp->gr_name);
		free(tmp->pw_name);
		free(tmp->d_name);
		free_list(tmp->is_dir);
		free(tmp);
		tmp = NULL;
	}
	return (1);
}

t_ls	*sorted_merge_reverse(t_ls *a, t_ls *b)
{
	t_ls *result;

	result = NULL;
	if (!a || !b)
		return (!a ? b : a);
	result = b;
	result->next = sorted_merge_reverse(a, b->next);
	return (result);
}

void	merge_sort_reverse(t_ls **head_ref)
{
	t_ls	*head;
	t_ls	*a;
	t_ls	*b;

	head = *head_ref;
	if (!head || !head->next)
		return ;
	front_back_split(head, &a, &b);
	merge_sort_reverse(&a);
	if (a->is_dir)
		merge_sort_reverse(&(a->is_dir));
	if (b->is_dir)
		merge_sort_reverse(&(b->is_dir));
	merge_sort_reverse(&b);
	*head_ref = sorted_merge_reverse(a, b);
}

void	merge_sort(t_ls **head, char flag)
{
	merge_sort_ascii(head, flag);
	if (MTIME)
		merge_sort_time(head, flag);
	if (REV)
		merge_sort_reverse(head);
}
