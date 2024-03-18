/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:30:33 by cogata            #+#    #+#             */
/*   Updated: 2024/03/04 15:51:29 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_node	*tokenizer(char *prompt)
{
	int		i;
	t_node	*head;
	t_node	*copy;
	t_node	*node;
	t_node	**ptr_list;

	head = NULL;
	check_quote_syntax(prompt);
	while (*prompt != '\0')
	{
		node = split_token(&prompt);
		if (node == NULL)
			break ;
		add_token(&head, node);
		// if(node->type == WORD);
		// 	count_fork++;
	}
	// node->last = 1;
	// print_lst_node(&head);
	copy = copy_list(head);
	ptr_list = ptr_to_list(copy);
	i = 0;
	while (ptr_list[i + 1])
		i++;
	ptr_list[i]->last = 1;
	return (head);
}

t_node	*copy_list(t_node *head)
{
	t_node	*tmp;
	t_node	*tmp2;
	t_node	*copy;
	t_node	*head_copy;

	tmp = head;
	copy = create_word_node(tmp->value, tmp->type, tmp->next_char);
	head_copy = copy;
	tmp = tmp->next;
	while (tmp)
	{
		tmp2 = create_word_node(tmp->value, tmp->type, tmp->next_char);
		copy->next = tmp2;
		copy = copy->next;
		tmp = tmp->next;
	}
	return (head_copy);
}

t_node	**ptr_to_list(t_node *head)
{
	int i;
	t_node *tmp;
	t_node *tmp2;
	t_node **ptr_list;
	int count_ptr;
	int count_pipe;

	tmp = head;
	count_ptr = 0;
	count_pipe = 0;
	while (tmp)
	{
		if (tmp->type == PIPE || tmp->type == AND || tmp->type == OR)
		{
			if (tmp->type == PIPE)
				count_pipe++;
			count_ptr++;
		}
		tmp = tmp->next;
	}
	count_ptr = (count_ptr * 2) + 1;
	ptr_list = ft_calloc(sizeof(t_node), count_ptr);
	i = 0;
	tmp = head;
	while (tmp)
	{
		if (tmp->type != PIPE && tmp->type != AND && tmp->type != OR)
		{
			ptr_list[i] = tmp;
			while (tmp->next && tmp->next->type != PIPE
				&& tmp->next->type != AND && tmp->next->type != OR)
				tmp = tmp->next;
			tmp2 = tmp->next;
			tmp->next = NULL;
		}
		else
		{
			ptr_list[i] = tmp;
			tmp2 = tmp->next;
			tmp->next = NULL;
		}
		tmp = tmp2;
		i++;
	}
	return (ptr_list);
}