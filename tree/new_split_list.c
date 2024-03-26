/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:53:10 by bbazagli          #+#    #+#             */
/*   Updated: 2024/03/25 17:26:36 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_node	*last_node(t_node *list)
{
	t_node	*last;

	last = list;
	while (last)
		last = last->next;
	return (last);
}

t_node *lookfor_operator(t_node *last)
{
	t_node	*cur;

	cur = last;
	while (cur)
	{
		if (cur->type == AND || cur->type == OR)
			return (cur);
		cur = cur->prev;
	}
	cur = last;
	while (cur)
	{
		if (cur->type == PIPE)
			return (cur);
		cur = cur->prev;
	}
	return (NULL);
}

t_node	*split_list(t_node *list)
{
	t_node	*last;
	t_node	*operator;
	t_node	*ptr_list[3];

	last = last_node(list);
	operator = lookfor_operator(last);
	if (!operator && list)
	{
		ptr_list[0] = list;
		ptr_list[1] = NULL;
		ptr_list[2] = NULL;
		return (ptr_list[0]);
	}
	if (operator)
	{
		ptr_list[0] = list;
		ptr_list[1] = operator;
		ptr_list[2] = operator->next;
		operator->prev->next = NULL;
		operator->prev = NULL;
		operator->next->prev = NULL;
	}
	return (ptr_list[0]);
}