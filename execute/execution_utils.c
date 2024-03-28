/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:28:29 by bbazagli          #+#    #+#             */
/*   Updated: 2024/03/28 09:55:41 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_status(t_tree *root, int status, int i)
{
	if (root->list->type == AND && WIFEXITED(status)
		&& WEXITSTATUS(status) != 0)
	{
		// free_mem(get_mem_address());
		return (ERROR);
	}
	if (root->list->type == OR && WIFEXITED(status) && WEXITSTATUS(status) == 0)
	{
		// free_mem(get_mem_address());
		return (ERROR);
	}
	return (OK);
}

void	execute_and_or(t_tree *root)
{
	static int	i;
	int			status;
	int			fork_id[2];

	i++;
	status = 0;
	fork_id[0] = fork();
	if (fork_id[0] == 0)
		execute_tree(root->left);
	else
		waitpid(fork_id[0], &status, 0);
	if (!check_status(root, status, i))
	{
		fork_id[1] = fork();
		if (fork_id[1] == 0)
			execute_tree(root->right);
		else
			waitpid(fork_id[1], &status, 0);
	}
	exit(WEXITSTATUS(status));
}

void	fork_process(int dup_fd, int std_fd, int close_fd, t_tree *root)
{
	dup2(dup_fd, std_fd);
	close(dup_fd);
	close(close_fd);
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
		fork_process(fd[WRITE], STDOUT_FILENO, fd[READ], root->left);
	close(fd[WRITE]);
	fork_id[1] = fork();
	if (fork_id[1] == -1)
		exit(1);
	if (fork_id[1] == 0)
		fork_process(fd[READ], STDIN_FILENO, fd[WRITE], root->right);
	close(fd[READ]);
	waitpid(fork_id[READ], &status, 0);
	waitpid(fork_id[WRITE], &status, 0);
	exit(WEXITSTATUS(status));
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
	args = allocate_mem(count_ptr + 1, sizeof(char *));
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
