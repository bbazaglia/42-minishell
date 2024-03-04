/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:30:15 by cogata            #+#    #+#             */
/*   Updated: 2024/03/04 12:30:16 by cogata           ###   ########.fr       */
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

/* int	check_quote_syntax(char *prompt)
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
} */
