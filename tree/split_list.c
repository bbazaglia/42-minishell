/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:55:40 by bbazagli          #+#    #+#             */
/*   Updated: 2024/03/25 17:26:14 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	lookfor_operator(t_node *tmp, t_node *list, int found)
{
	while (tmp)
	{
		if (tmp->type == AND || tmp->type == OR)
		{
			found = 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (found == 0)
	{
		tmp = list;
		while (tmp)
		{
			if (tmp->type == PIPE)
			{
				found = 2;
				break ;
			}
			tmp = tmp->next;
		}
	}
	return (found);
}

// int	lookfor_operator(t_node *tmp, t_node *last, int found)
// {
// 	while (tmp)
// 	{
// 		if (tmp->type == AND || tmp->type == OR)
// 		{
// 			found = 1;
// 			break ;
// 		}
// 		tmp = tmp->prev;
// 	}
// 	if (found == 0)
// 	{
// 		tmp = last;
// 		while (tmp)
// 		{
// 			if (tmp->type == PIPE)
// 			{
// 				found = 2;
// 				break ;
// 			}
// 			tmp = tmp->prev;
// 		}
// 	}
// 	return (found);
// }

void	found_and_or(int i, int found, t_node *tmp, t_node **ptr_list)
{
	t_node	*tmp2;

	found = 0;
	while (tmp)
	{
		if (found == 0 && (tmp->type == AND || tmp->type == OR))
		{
			found = 1;
			ptr_list[i] = tmp;
			tmp2 = tmp->next;
			tmp->next = NULL;
		}
		else
		{
			ptr_list[i] = tmp;
			while ((found == 1 && tmp->next) || (tmp->next
					&& tmp->next->type != AND && tmp->next->type != OR))
				tmp = tmp->next;
			tmp2 = tmp->next;
			tmp->next = NULL;
		}
		tmp = tmp2;
		i++;
	}
}

// void	found_and_or(int i, int found, t_node *head, t_node **ptr_list)
// {
// 	t_node *tmp = head;
// 	t_node	*tmp2;

// 	tmp2 = NULL;
// 	found = 0;
// 	while (tmp->next)
// 		tmp = tmp->next;
// 	while (tmp)
// 	{
// 		if (found == 0 && (tmp->type == AND || tmp->type == OR))
// 		{
// 			found = 1;
// 			ptr_list[i] = tmp;
// 			tmp2 = tmp->next;
// 			tmp->next->prev = NULL; 
// 			tmp->prev->next = NULL;
// 		}
// 		else
// 		{
// 			while ((found == 1 && tmp->prev) || (tmp->prev
// 					&& tmp->prev->type != AND && tmp->prev->type != OR))
// 				tmp = tmp->prev;
// 			ptr_list[i] = tmp;
// 			tmp2 = tmp->prev;
// 			if (tmp2)
// 				tmp2->next = NULL; 
// 		}
// 		tmp = tmp2;
// 		i++;
// 	}
// }

void	found_pipe(int i, int found, t_node *tmp, t_node **ptr_list)
{
	t_node	*tmp2;

	found = 0;
	while (tmp)
	{
		if (found == 0 && tmp->type == PIPE)
		{
			found = 1;
			ptr_list[i] = tmp;
			tmp2 = tmp->next;
			tmp->next = NULL;
		}
		else
		{
			ptr_list[i] = tmp;
			while ((found == 1 && tmp->next) || (tmp->next
					&& tmp->next->type != PIPE))
				tmp = tmp->next;
			tmp2 = tmp->next;
			tmp->next = NULL;
		}
		tmp = tmp2;
		i++;
	}
}

t_node	*reverse_list(t_node *list)
{
	t_node	*last;

	last = list;
	while (last)
		last = last->next;
	return (last);
}

t_node	**split_list(t_node *list)
{
	t_node	*tmp;
	t_node	*tmp2;
	t_node	**ptr_list;
	int		i;
	int		found;
	t_node	*last;

	i = 0;
	found = 0;
	last = reverse_list(list);
	tmp = last;
	found = lookfor_operator(tmp, last, found);
	if (found == 0)
		return (NULL);
	ptr_list = allocate_mem(3, sizeof(t_node *));
	i = 0;
	tmp = list;
	if (found == 1)
		found_and_or(i, found, tmp, ptr_list);
	else if (found == 2)
		found_pipe(i, found, tmp, ptr_list);
	return (ptr_list);
}
