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
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <ctype.h>

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

enum    e_error
{
    SYNTAX_ERROR = 1,
    ERROR
};

typedef struct s_node
{
	char			*value;
	int				type;
	struct s_node	*next;
}					t_node;

#endif