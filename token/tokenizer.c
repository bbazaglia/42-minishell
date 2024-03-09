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
	t_node	*head;
	t_node	*node;

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
