/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:30:33 by cogata            #+#    #+#             */
/*   Updated: 2024/03/04 12:30:34 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	tokenizer(char *prompt)
{
	int		i;
	t_node	*head;
	t_node	*node;

	head = NULL;
	check_quote_syntax(prompt);
	i = 0;
	while (*prompt != '\0')
	{
		node = split_token(&prompt);
		if (node == NULL)
			break ;
		add_token(&head, node);
	}
	print_lst_node(&head);
}
