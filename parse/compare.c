/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:30:27 by cogata            #+#    #+#             */
/*   Updated: 2024/03/04 12:30:29 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	if (*to_find == '\0')
		return (str);
	if (*str == '\0')
		return (0);
	i = 0;
	while (str[i])
	{
		j = 0;
		if (str[i] == to_find[j])
		{
			while (to_find[j] && str[i + j] == to_find[j])
				j++;
		}
		if (to_find[j] == '\0')
			return (&str[i]);
		i++;
	}
	return (0);
}

void	compare(t_node **node, char **prompt, char *temp, int i)
{
	if (temp[i] == '&' && temp[i + 1] == '&')
		*node = create_meta_node(prompt, "&&", 2);
	else if (temp[i] == '|' && temp[i + 1] == '|')
		*node = create_meta_node(prompt, "||", 2);
	else if (temp[i] == '|')
		*node = create_meta_node(prompt, "|", 1);
	else if (temp[i] == '>' && temp[i + 1] == '>')
		*node = create_meta_node(prompt, ">>", 2);
	else if (temp[i] == '<' && temp[i + 1] == '<')
		*node = create_meta_node(prompt, "<<", 2);
	else if (temp[i] == '<')
		*node = create_meta_node(prompt, "<", 1);
	else if (temp[i] == '>')
		*node = create_meta_node(prompt, ">", 1);
	else if (temp[i] == '$')
		*node = compare_word(prompt, EXPAND);
	else if (ft_strchr("|<> \"\'", temp[i]) == 0)
		*node = compare_word(prompt, WORD);
	else if (temp[i] && temp[i + 1] && temp[i] == '\'')
		*node = compare_quote(prompt, '\'', SING_QUOTE);
	else if (temp[i] && temp[i + 1] && temp[i] == '"')
		*node = compare_quote(prompt, '"', DOUB_QUOTE);
}

t_node	*compare_word(char **prompt, int type)
{
	int		i;
	char	*temp;
	char	*word;
	t_node	*node;

	i = 0;
	temp = *prompt;
	while (ft_strchr("|<> \"\'", temp[i]) == 0)
	{
		if (temp[i] == '&' && temp[i + 1] && temp[i + 1] == '&')
			break ;
		i++;
		*prompt = *prompt + 1;
	}
	word = ft_strndup(temp, i);
	node = create_word_node(word, type, temp[i]);
	return (node);
}

t_node	*compare_quote(char **prompt, char symbol, int type)
{
	int		i;
	char	*temp;
	char	*quote;
	t_node	*node;

	i = 1;
	temp = *prompt;
	*prompt = *prompt + 1;
	while (temp[i] && temp[i] != symbol)
	{
		i++;
		*prompt = *prompt + 1;
	}
	quote = ft_strndup(temp, i + 1);
	node = create_word_node(quote, type, temp[i + 1]);
	*prompt = *prompt + 1;
	return (node);
}

t_node	*split_token(char **prompt)
{
	int		i;
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
	compare(&node, prompt, temp, i);
	return (node);
}
