/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:30:39 by cogata            #+#    #+#             */
/*   Updated: 2024/03/21 15:20:55 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_node	*tokenizer(char *input)
{
	int		i;
	t_node	*head;
	t_node	*copy;
	t_node	*node;

	head = NULL;
	check_quote_syntax(input);
	while (*input != '\0')
	{
		node = split_token(&input);
		if (node == NULL)
			break ;
		add_token(&head, node);
	}
	return (head);
}

t_node	*split_token(char **input)
{
	int		i;
	char	*temp;
	t_node	*node;

	i = 0;
	temp = *input;
	node = NULL;
	while (temp[i] == ' ')
	{
		i++;
		*input = *input + 1;
	}
	lookfor_token(&node, input, temp, i);
	return (node);
}

void	add_token(t_node **head, t_node *node)
{
	t_node	*temp;

	temp = *head;
	if (*head == NULL)
		*head = node;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = node;
	}
}

t_node	*create_meta_node(char **input, char *str, int move)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->value = ft_strdup(str);
	node->fd = -1;
	node->next = NULL;
	if (!ft_strncmp(str, "&&", 2))
		node->type = AND;
	else if (!ft_strncmp(str, "||", 2))
		node->type = OR;
	else if (!ft_strncmp(str, "|", 1))
		node->type = PIPE;
	else if (!ft_strncmp(str, ">>", 2))
		node->type = APPEND;
	else if (!ft_strncmp(str, "<<", 2))
		node->type = HEREDOC;
	else if (!ft_strncmp(str, "<", 1))
		node->type = IN_REDIR;
	else if (!ft_strncmp(str, ">", 1))
		node->type = OUT_REDIR;
	*input = *input + move;
	node->next_char = input[0][0];
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
	node->fd = -1;
	node->next = NULL;
	return (node);
}
