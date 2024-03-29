/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:33:17 by cogata            #+#    #+#             */
/*   Updated: 2024/02/28 15:33:19 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <ctype.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

enum				e_token
{
	AND = 1,
	OR,
	PIPE,
	IN_REDIR,
	OUT_REDIR,
	APPEND,
	HEREDOC,
	WORD,
	EXPAND,
	SING_QUOTE,
	DOUB_QUOTE,
};

enum				e_error
{
	SYNTAX_ERROR = 1,
	ERROR
};

typedef struct s_node
{
	char			*value;
	int				type;
	char			next_char;
	struct s_node	*next;
}					t_node;

// Compare functions
void				compare(t_node **node, char **prompt, char *temp, int i);
t_node				*compare_word(char **prompt, int type);
t_node				*compare_quote(char **prompt, char symbol, int type);

// Token functions
void				tokenizer(char *prompt);
t_node				*split_token(char **prompt);
t_node				*create_meta_node(char **prompt, char *str, int move);
t_node				*create_word_node(char *value, int type, char next_char);
void				add_token(t_node **head, t_node *node);

// Syntax functions
int					check_quote_syntax(char *prompt);

// Error message
void				error(int err);

// Utils
void				print_lst_node(t_node **head);
char				*ft_strndup(char *s, size_t n);

#endif