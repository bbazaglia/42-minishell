/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:33:17 by cogata            #+#    #+#             */
/*   Updated: 2024/03/25 10:27:53 by bbazagli         ###   ########.fr       */
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
	struct s_node	*next;
	struct s_node	*prev;
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
void				sigint_cmd_handler(int signo);

//Parser functions
void				parse(char *input, t_tree **root);
t_node				*tokenizer(char *input);
t_node				*split_token(char **input);
void				add_token(t_node **head, t_node *node);
void				lookfor_token(t_node **node, char **input, char *temp,
						int i);
t_node				*lookfor_word(char **input, int type);
t_node				*lookfor_quotes(char **input, char symbol, int type);
t_node				*create_meta_node(char **input, char *str, int move);
t_node				*create_word_node(char *value, int type, char next_char);

// Syntax functions
int					check_quote_syntax(char *input);
int					check_syntax(t_node *node);

// Tree functions
void				build_tree(t_tree **root, t_node *list);
t_node				**split_list(t_node *list);
int					lookfor_operator(t_node *tmp, t_node *list, int found);
void				found_and_or(int i, int found, t_node *tmp,
						t_node **ptr_list);
void				found_pipe(int i, int found, t_node *tmp,
						t_node **ptr_list);

// Execution functions
char				**list_to_array(t_node *head);
void				execute(t_tree *root);
int					is_single_node(t_tree *root);
void				execute_fork(t_tree *root);
void				execute_tree(t_tree *root);
void				execute_and_or(t_tree *root);
void				execute_pipe(t_tree *root);
void				execute_command(t_tree *root);
void				check_status(t_tree *root);
void				fork_process(int fd, int std_fd, t_tree *root);

// Environment functions
char				**insert_env_var(char **env_table, char *key, char *value);
char				**add_env_var(char **env_table, char *var_line);
char				**modify_env_var(char **env_table, char *var_new_line,
						char *var_old_line);
char				**del_env_var(char **env_table, char *key);
char				**update_env_table(char *var_line, int size);
char				**get_env_table(void);
void				free_env_table(char **env_table);

// Heredoc functions
int					create_heredoc_temp(void);
void				check_delimiter(t_node *head, char *heredoc_input,
						char *delimiter);
void				check_heredoc(t_node *head);

// Utils functions
int					error(int err);
void				print_lst_node(t_node **head);
void				printTree(t_tree *n);
int					maxDepth(t_tree *n);

#endif