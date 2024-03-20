/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 12:21:53 by bbazagli          #+#    #+#             */
/*   Updated: 2024/03/20 11:39:37 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**list_to_array(t_node *head)
{
	char	**args;
	t_node	*tmp;
	int		i;
	int		count_ptr;

	count_ptr = 0;
	tmp = head;
	while (tmp)
	{
		count_ptr++;
		tmp = tmp->next;
	}
	args = ft_calloc(count_ptr + 1, sizeof(char *));
	i = 0;
	while (i < count_ptr)
	{
		args[i] = ft_strdup(head->value);
		i++;
		head = head->next;
	}
	args[i] = NULL;
	return (args);
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
		exit(1);
}

void	execute_tree(t_tree *root)
{
	if (root->list->type == AND || root->list->type == OR)
		execute_and_or(root);
	else if (root->list->type == PIPE)
		execute_pipe(root);
	// else if (root->list->type >= IN_REDIR && root->list->type <= HEREDOC)
	// else if (root->left)
	// 	execute_command(root->left);
	// else if (root->right)
	// 	execute_command(root->right);
	// else if (root->list->type >= WORD && root->list->type <= DOUB_QUOTE)
	// 	execute_fork()
	else
		execute_command(root);
}

void	execute_and_or(t_tree *root)
{
	int	status;
	int	fork_id;

	if (root->left->list->type >= WORD && root->left->list->type <= DOUB_QUOTE)
	{
		fork_id = fork();
		if (fork_id == 0)
			execute_tree(root->left);
		waitpid(fork_id, &status, NULL);
	}
	else if (root->left)
		execute_tree(root->left);
	if (root->list->type == AND && WIFEXITED(status)
		&& WEXITSTATUS(status) != 0)
		exit(1);
	if (root->list->type == OR && WIFEXITED(status) && WEXITSTATUS(status) == 0)
		exit(1);
	if (root->right->list->type >= WORD
		&& root->right->list->type <= DOUB_QUOTE)
	{
		fork_id = fork();
		if (fork_id == 0)
			execute_tree(root->right);
		waitpid(fork_id, &status, NULL);
	}
	else if (root->right)
		execute_tree(root->right);
}

void	execute_pipe(t_tree *root)
{
	signal(SIGINT, fd_handler);
	int fork_id[2];
	int fd[2];
	int status;
	pipe(fd);

	fork_id[0] = fork();
	if (fork_id[0] == -1)
		exit(1);

	// to do: check for redirect

	// open first fork
	if (fork_id[0] == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute_tree(root->left);
	}
	close(fd[1]);
	// open second fork
	fork_id[1] = fork();
	if (fork_id[1] == -1)
		exit(1);
	if (fork_id[1] == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		execute_tree(root->right);
	}
	close(fd[0]);
	waitpid(fork_id[0], &status, NULL);
	waitpid(fork_id[1], &status, NULL);
}