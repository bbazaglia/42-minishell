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

void	lookfor_operator(t_node *list, t_node **ptr_list, int i)
{
	t_node	*cur;
	t_node	**ptr_list;

	cur = list;
	while (cur->next)
		cur = cur->next;
	while (cur)
	{
		if (cur->type == PIPE)
		{
			// ptr to pipe
			ptr_list[i] = cur;
			i++;
			cur->prev->next = NULL;
			cur->next->prev = NULL;
			cur->next = NULL;
			cur->prev = NULL;
			cur = cur->next;
			// ptr to the right node
			ptr_list[i] = cur;
			i++;
			// ptr to the left node is already the head of the list
			return ;
		}
	}
}