/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MergeSort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 18:48:03 by tblaudez          #+#    #+#             */
/*   Updated: 2018/07/17 18:48:05 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			front_back_split(t_ls *source, t_ls **front_ref,
t_ls **back_ref)
{
	t_ls	*fast;
	t_ls	*slow;

	slow = source;
	fast = source->next;
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*front_ref = source;
	*back_ref = slow->next;
	slow->next = NULL;
}

static t_ls		*sorted_merge_ascii(t_ls *a, t_ls *b)
{
	t_ls	*result;

	result = NULL;
	if (!a || !b)
		return (!a ? b : a);
	if (ft_strcmp(a->d_name, b->d_name) < 0)
	{
		result = a;
		result->next = sorted_merge_ascii(a->next, b);
	}
	else
	{
		result = b;
		result->next = sorted_merge_ascii(a, b->next);
	}
	return (result);
}

void			merge_sort_ascii(t_ls **head_ref, char flag)
{
	t_ls	*head;
	t_ls	*a;
	t_ls	*b;

	head = *head_ref;
	if (!head || !head->next)
		return ;
	front_back_split(head, &a, &b);
	merge_sort_ascii(&a, flag);
	if (a->is_dir)
		merge_sort_ascii(&(a->is_dir), flag);
	if (b->is_dir)
		merge_sort_ascii(&(b->is_dir), flag);
	merge_sort_ascii(&b, flag);
	*head_ref = sorted_merge_ascii(a, b);
}

static t_ls		*sorted_merge_time(t_ls *a, t_ls *b)
{
	t_ls *result;

	result = NULL;
	if (!a || !b)
		return (!a ? b : a);
	if (a->modif_time >= b->modif_time)
	{
		result = a;
		result->next = sorted_merge_time(a->next, b);
	}
	else
	{
		result = b;
		result->next = sorted_merge_time(a, b->next);
	}
	return (result);
}

void			merge_sort_time(t_ls **head_ref, char flag)
{
	t_ls	*head;
	t_ls	*a;
	t_ls	*b;

	head = *head_ref;
	if (!head || !head->next)
		return ;
	front_back_split(head, &a, &b);
	merge_sort_time(&a, flag);
	if (a->is_dir)
		merge_sort_time(&(a->is_dir), flag);
	if (b->is_dir)
		merge_sort_time(&(b->is_dir), flag);
	merge_sort_time(&b, flag);
	*head_ref = sorted_merge_time(a, b);
}
