/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:30:33 by cogata            #+#    #+#             */
/*   Updated: 2024/03/20 16:40:41 by cogata           ###   ########.fr       */
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
	}
	// print_lst_node(&head);
	return (head);
}
