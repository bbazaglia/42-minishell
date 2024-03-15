/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:33:17 by cogata            #+#    #+#             */
/*   Updated: 2024/03/08 10:53:49 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <ctype.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>

extern volatile int	g_heredoc_signal;

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
	MALLOC_FAILED,
	SIGNAL_ERROR,
};

typedef struct s_node
{
	char			*value;
	int				type;
	char			next_char;
	int				fd;
	struct s_node	*next;
}					t_node;

typedef struct s_tree
{
	t_node			*list;
	struct s_tree	*right;
	struct s_tree	*left;
}					t_tree;

// Signal functions
void				initialize_signals(void);
void				sigint_handler(int signo);
void				heredoc_handler(int signo);

// Terminal functions
void				set_terminal_attributes(void);

// Compare functions
void				compare(t_node **node, char **prompt, char *temp, int i);
t_node				*compare_word(char **prompt, int type);
t_node				*compare_quote(char **prompt, char symbol, int type);

// Token functions
t_node				*tokenizer(char *prompt);
t_node				*split_token(char **prompt);
t_node				*create_meta_node(char **prompt, char *str, int move);
t_node				*create_word_node(char *value, int type, char next_char);
void				add_token(t_node **head, t_node *node);

// Syntax functions
int					check_quote_syntax(char *prompt);
void				check_syntax(t_node *node);

//Tree
void				build_tree(t_tree **root, t_node *list);
void				printTree(t_tree *n);
t_node				**split_list(t_node *list);

//Set env
char				**insert_env_var(char **env_table, char *key, char *value);
char				**add_env_var(char **env_table, char *var_line);
char				**modify_env_var(char **env_table, char *var_new_line,
						char *var_old_line);
char				**del_env_var(char **env_table, char *key);
char				**update_env_table(char *var_line, int size);
char				**get_env_table(void);
void				free_env_table(char **env_table);

// Heredoc
void				check_heredoc(t_node *head);
int					create_heredoc_temp(void);

// Error message
void				error(int err);

// Utils
void				print_lst_node(t_node **head);
char				*ft_strndup(char *s, size_t n);
void				printTree(t_tree *n);
int maxDepth(t_tree* n);

#endif