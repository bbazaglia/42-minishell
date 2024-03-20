/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:30:39 by cogata            #+#    #+#             */
/*   Updated: 2024/03/20 16:37:56 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_token(t_node **head, t_node *node)
{
	t_node	*temp;

	temp = *head;
	if (*head == NULL)
		*head = node;
	else
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = node;
	}
}

t_node	*create_meta_node(char **prompt, char *str, int move)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->value = ft_strdup(str);
	node->next = NULL;
	if (ft_strncmp(str, "&&", 2) == 0)
		node->type = AND;
	else if (ft_strncmp(str, "||", 2) == 0)
		node->type = OR;
	else if (ft_strncmp(str, "|", 1) == 0)
		node->type = PIPE;
	else if (ft_strncmp(str, ">>", 2) == 0)
		node->type = APPEND;
	else if (ft_strncmp(str, "<<", 2) == 0)
		node->type = HEREDOC;
	else if (ft_strncmp(str, "<", 1) == 0)
		node->type = IN_REDIR;
	else if (ft_strncmp(str, ">", 1) == 0)
		node->type = OUT_REDIR;
	*prompt = *prompt + move;
	node->next_char = prompt[0][0];
	return (node);
}

t_node	*create_word_node(char *value, int type, char next_char)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->value = value;
	node->type = type;
	node->next_char = next_char;
	node->next = NULL;
	return (node);
}
