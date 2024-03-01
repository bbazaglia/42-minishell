/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:33:08 by cogata            #+#    #+#             */
/*   Updated: 2024/02/28 15:33:13 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	error(int err)
{
	if (err == SYNTAX_ERROR)
		ft_putstr_fd("Syntax Error\n", 2);
	exit(EXIT_FAILURE);
}

int	check_quote_syntax(char *prompt)
{
	int	quote;

	quote = 0;
	while (*prompt)
	{
		if (*prompt == '"' || *prompt == '\'')
		{
			if (*prompt == '"')
			{
				quote = 1;
				prompt++;
				while (*prompt && *prompt != '"')
					prompt++;
				if (*prompt == '"')
					quote++;
				if (quote % 2 != 0)
					error(SYNTAX_ERROR);
			}
			if (*prompt == '\'')
			{
				quote = 1;
				prompt++;
				while (*prompt && *prompt != '\'')
					prompt++;
				if (*prompt == '\'')
					quote++;
				if (quote % 2 != 0)
					error(SYNTAX_ERROR);
			}
		}
		prompt++;
	}
	return (0);
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
		{
			temp = temp->next;
		}
		temp->next = node;
	}
}

void	print_lst_node(t_node **head)
{
	int		i;
	t_node	*temp;

	i = 0;
	temp = *head;
	while (temp)
	{
		printf("node %d\n", i);
		printf("value: %s\n", temp->value);
		printf("type: %d\n\n", temp->type);
		temp = temp->next;
		i++;
	}
}

char	*ft_strndup(char *s, size_t n)
{
	int		i;
	char	*dest;

	dest = malloc(n + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (n != 0 && s[i])
	{
		dest[i] = s[i];
		i++;
		n--;
	}
	dest[i] = '\0';
	return (dest);
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
	
	else if (ft_strncmp(str, "$", 1) == 0)
		node->type = EXPAND;
	*prompt = *prompt + move;
	return (node);
}

t_node	*create_word_node(char *value, int type)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->value = value;
	node->type = type;
	node->next = NULL;
	return (node);
}

t_node	*compare(char **prompt)
{
	int		i;
	char	*value;
	char	*temp;
	t_node	*node;

	i = 0;
	temp = *prompt;
	node = NULL;
	while (temp[i] == ' ')
	{
		i++;
		*prompt = *prompt + 1;
	}
	if (temp[i] == '&' && temp[i + 1] == '&')
		node = create_meta_node(prompt, "&&", 2);
	else if (temp[i] == '|' && temp[i + 1] == '|')
		node = create_meta_node(prompt, "||", 2);
	else if (temp[i] == '|')
		node = create_meta_node(prompt, "|", 1);
	else if (temp[i] == '>' && temp[i + 1] == '>')
		node = create_meta_node(prompt, ">>", 2);
	else if (temp[i] == '<' && temp[i + 1] == '<')
		node = create_meta_node(prompt, "<<", 2);
	else if (temp[i] == '<')
		node = create_meta_node(prompt, "<", 1);
	else if (temp[i] == '>')
		node = create_meta_node(prompt, ">", 1);
	else if (temp[i] == '$')
		node = create_meta_node(prompt, "$", 1);
	else if (temp[i] && temp[i + 1] && temp[i] == '\'')
	{
		i = 0;
		i++;
		temp = *prompt;
		*prompt = *prompt + 1;
		while (temp[i] && temp[i] != '\'')
		{
			i++;
			*prompt = *prompt + 1;
		}
		value = ft_strndup(temp, i+1);
		node = create_word_node(value, SING_QUOTE);
		*prompt = *prompt + 1;
	}
	else if (temp[i] && temp[i + 1] && temp[i] == '"')
	{
		i = 0;
		i++;
		temp = *prompt;
		*prompt = *prompt + 1;
		while (temp[i] && temp[i] != '"')
		{
			i++;
			*prompt = *prompt + 1;
		}
		value = ft_strndup(temp, i+1);
		node = create_word_node(value, DOUB_QUOTE);
		*prompt = *prompt + 1;
	}	
	else if(ft_strchr("&|<> \"\'", temp[i]) == 0)
	{
		i = 0;
		temp = *prompt;
		while (ft_strchr("&|<> \"\'", temp[i]) == 0)
		{
			i++;
			*prompt = *prompt + 1;
		}
		value = ft_strndup(temp, i);
		node = create_word_node(value, WORD);
	}
	return (node);
}

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
		node = compare(&prompt);
		if(node == NULL)
			break;
		add_token(&head, node);
	}
	print_lst_node(&head);
}

int	main(void)
{
	char	*prompt;

	// prompt = "echo \"hello\"";
	prompt = readline("minishell: ");
	tokenizer(prompt);
	return (0);
}
