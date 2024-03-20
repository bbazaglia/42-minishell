/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:30:15 by cogata            #+#    #+#             */
/*   Updated: 2024/03/05 10:56:25 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_quote_syntax(char *prompt)
{
	int		inside_quote;
	char	quote_type;

	inside_quote = 0;
	quote_type = '\0';
	while (*prompt)
	{
		if (*prompt == '"' || *prompt == '\'')
		{
			if (!inside_quote)
			{
				inside_quote = 1;
				quote_type = *prompt;
			}
			else if (*prompt == quote_type)
			{
				inside_quote = 0;
				quote_type = '\0';
			}
		}
		prompt++;
	}
	if (inside_quote)
		error(SYNTAX_ERROR);
	return (0);
}

/*
1) the first token cannot be an operator or a pipe;
2) operators and pipe cannot be followed by another operator or pipe;
3) a redirect cannot be followed by another redirect, a pipe or an operator;
4) the last token can only be a word (expansion or quotes)

NOTE: echo hello | " " does not return error, check for it before execution
*/
void	check_syntax(t_node *node)
{
	if (node->type >= AND && node->type <= PIPE)
		error(SYNTAX_ERROR);
	while (node->next)
	{
		if (node->type >= AND && node->type <= PIPE)
		{
			if (node->next->type >= AND && node->next->type <= PIPE)
				error(SYNTAX_ERROR);
		}
		if (node->type >= IN_REDIR && node->type <= HEREDOC)
		{
			if (node->next->type >= AND && node->next->type <= HEREDOC)
				error(SYNTAX_ERROR);
		}
		node = node->next;
	}
	if (node->type >= AND && node->type <= HEREDOC)
		error(SYNTAX_ERROR);
}
