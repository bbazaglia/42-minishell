/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:55:40 by bbazagli          #+#    #+#             */
/*   Updated: 2024/03/26 11:30:39 by bbazagli         ###   ########.fr       */
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
	while (last->next)
		last = last->next;
	return (last);
}

t_node	*lookfor_operator(t_node *last)
{
	t_node	*cur;

	cur = last;
	while (cur->prev)
	{
		if (cur->type == AND || cur->type == OR)
			return (cur);
		cur = cur->prev; 
	}
	cur = last;
	while (cur->prev)
	{
		if (cur->type == PIPE)
			return (cur);
		cur = cur->prev;
	}
	return (NULL);
}

t_node	**split_list(t_node *list)
{
	t_node *last;
	t_node *operator;
	t_node **ptr_list;

	last = last_node(list);
	operator = lookfor_operator(last);
	if (!operator && list)
		return NULL;
	if (operator)
	{
		ptr_list = allocate_mem(3, sizeof(t_node *));
		ptr_list[0] = list;
		ptr_list[1] = operator;
		ptr_list[2] = operator->next;
		operator->prev->next = NULL;
		operator->prev = NULL;
		operator->next->prev = NULL;
	}
	return (ptr_list);
}