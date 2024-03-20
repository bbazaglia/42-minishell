/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:33:17 by cogata            #+#    #+#             */
/*   Updated: 2024/03/20 15:22:40 by cogata           ###   ########.fr       */
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
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

extern volatile int	g_signal;

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
	int				last;
	struct s_node	*next;
}					t_node;

typedef struct s_tree
{
	t_node			*list;
	struct s_tree	*right;
	struct s_tree	*left;
	int				pipe_read;
}					t_tree;

// Signal functions
void				initialize_signals(void);
void				sigint_handler(int signo);
void				sigint_cmd_handler(int signo);

// Terminal functions
void				set_terminal_attributes(void);

// Compare functions
void				compare(t_node **node, char **prompt, char *temp, int i);
t_node				*compare_word(char **prompt, int type);
t_node				*compare_quote(char **prompt, char symbol, int type);

//Parse function
void				parse(char *input, t_tree **root);

// Token functions
t_node				*tokenizer(char *prompt);
t_node				*split_token(char **prompt);
t_node				*create_meta_node(char **prompt, char *str, int move);
t_node				*create_word_node(char *value, int type, char next_char);
void				add_token(t_node **head, t_node *node);
t_node				**ptr_to_list(t_node *head);
t_node				*copy_list(t_node *head);

// Syntax functions
int					check_quote_syntax(char *prompt);
void				check_syntax(t_node *node);

// Tree
void				build_tree(t_tree **root, t_node *list);
void				printTree(t_tree *n);
t_node				**split_list(t_node *list);
void				count_processes(t_tree *root, int *count_fork);
int					**allocate_forks(int count_fork);
void				execute_fork_command(t_tree *root);
void				execute(t_tree *root);
int					is_single_node(t_tree *root);

// Execution
void				execute_tree(t_tree *root);
void				execute_and_or(t_tree *root);
void				execute_pipe(t_tree *root);
char				**list_to_array(t_node *head);
void				execute_command(t_tree *root);

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
int					create_heredoc_temp(void);
void				check_delimiter(t_node *head, char *heredoc_input,
						char *delimiter);
void				check_heredoc(t_node *head);

// Error message
void				error(int err);

// Utils
void				print_lst_node(t_node **head);
void				printTree(t_tree *n);
int					maxDepth(t_tree *n);

#endif