/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:28:29 by bbazagli          #+#    #+#             */
/*   Updated: 2024/03/21 14:19:36 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_status(t_tree *root)
{
	int	status;

	if (root->list->type == AND && WIFEXITED(status)
		&& WEXITSTATUS(status) != 0)
		exit(1);
	if (root->list->type == OR && WIFEXITED(status) && WEXITSTATUS(status) == 0)
		exit(1);
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
	check_status(root);
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

void	fork_process(int fd, int std_fd, t_tree *root)
{
	dup2(fd, std_fd);
	close(fd);
	execute_tree(root);
}

void	execute_pipe(t_tree *root)
{
	int	fork_id[2];
	int	fd[2];
	int	status;

	pipe(fd);
	fork_id[0] = fork();
	if (fork_id[0] == -1)
		exit(1);
	// to do: check for redirect
	if (fork_id[0] == 0)
		fork_process(fd[1], STDOUT_FILENO, root->left);
	close(fd[1]);
	fork_id[1] = fork();
	if (fork_id[1] == -1)
		exit(1);
	if (fork_id[1] == 0)
		fork_process(fd[0], STDIN_FILENO, root->right);
	close(fd[0]);
	waitpid(fork_id[0], &status, NULL);
	waitpid(fork_id[1], &status, NULL);
}

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
