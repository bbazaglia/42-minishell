/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 12:21:53 by bbazagli          #+#    #+#             */
/*   Updated: 2024/03/26 11:04:09 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute(t_tree *root)
{
	if (root == NULL)
		return ;
	signal(SIGINT, sigint_cmd_handler);
	if (is_single_node(root))
		execute_fork(root);
	else
		execute_tree(root);
}

int	is_single_node(t_tree *root)
{
	int	is_single;

	is_single = 1;
	if (root && (root->right || root->left))
		is_single = 0;
	return (is_single);
}

void	execute_fork(t_tree *root)
{
	int		fork_id;
	int		status;
	char	*path_name;
	char	*path;
	char	**args;

	path = "/usr/bin/";
	path_name = ft_strjoin(path, root->list->value);
	
	args = list_to_array(root->list);
	fork_id = fork();
	if (fork_id == -1)
		exit(1);
	else if (fork_id == 0)
	{
		if (execve(path_name, args, NULL) == -1)
		{
			free_mem(get_mem_address());
			exit(1);
		}
	}
	waitpid(fork_id, &status, 0);
}

void	execute_tree(t_tree *root)
{
	if (root->list->type == AND || root->list->type == OR)
		execute_and_or(root);
	else if (root->list->type == PIPE)
		execute_pipe(root);
	else
		execute_command(root);
}

void	execute_command(t_tree *root)
{
	char	*path_name;
	char	*path;
	char	**args;

	path = "/usr/bin/";
	path_name = ft_strjoin(path, root->list->value);
	args = list_to_array(root->list);
	if (execve(path_name, args, NULL) == -1)
	{
		free_mem(get_mem_address());
		exit(1);
	}
}
