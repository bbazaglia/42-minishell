/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:03:03 by bbazagli          #+#    #+#             */
/*   Updated: 2024/03/15 17:40:57 by bbazagli         ###   ########.fr       */
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

void	execute_tree(t_tree *root, int **forks, int *pos)
{
	if (root->left && root->left->left)
		execute_tree(root->left, forks, pos);
	if (root)
		execute_leaf(root, forks, pos);
	if (root->right && root->right->left)
		execute_tree(root->right, forks, pos);
}

void	execute_leaf(t_tree *root, int **forks, int *pos)
{
	char	*path_name;
	char	*path;
	char	**args;
	// int		fork_id;
	int		status;

	path = "/usr/bin/";
	path_name = ft_strjoin(path, root->list->value);
	args = list_to_array(root->list);
	
	if (root->list->type == AND || root->list->type == OR)
		execute_and_or(root, forks, pos);
	else if (root->list->type == PIPE)
		execute_pipe(root, forks, pos);
	else
	{
		forks[*pos][0] = fork();
		if (forks[*pos][0] == -1)
			exit(1);
		else if (forks[*pos][0] == 0)
		{
			if (execve(path_name, args, NULL) == -1)
				exit(1);
		}
		if(root->list->last == 1)
			wait_forks(forks, *pos);
		*pos = *pos + 1;
	}
}

void	execute_and_or(t_tree *root, int **forks, int *pos)
{
	// int		fork_id;
	int		status;
	char	*path_name;
	char	*path;
	char	**args;

	path = "/usr/bin/";
	path_name = ft_strjoin(path, root->list->value);
	args = list_to_array(root->list);
	if (root->left->list->type >= IN_REDIR && root->left->list->type <= DOUB_QUOTE)
	{
		forks[*pos][0] = fork();
		if (forks[*pos][0] == -1)
			exit(1);
		else if (forks[*pos][0] == 0)
		{
			if (execve(path_name, args, NULL) == -1)
				exit(1);
		}
		// if(root->list->last == 1)
		// 	wait_forks(forks, pos);
		*pos = *pos + 1;
	}
	if (root->list->type == AND && WIFEXITED(status)
		&& WEXITSTATUS(status) != 0)
		exit(1);
	if (root->list->type == OR && WIFEXITED(status) && WEXITSTATUS(status) == 0)
		exit(1);
}

void	execute_pipe(t_tree *root, int **forks, int *pos)
{
	// int fork_id;
	int status;
	char *path_name;
	char *path;
	char **args;
	int fd[2];

	path = "/usr/bin/";
	pipe(fd);
	forks[*pos][0] = fork();
	if (forks[*pos][0] == -1)
		exit(1);
	else if (forks[*pos][0] == 0)
	{
		if (root->pipe_read != -1)
		{
			dup2(fd[0], root->pipe_read);
			close(fd[0]);
		}
		path_name = ft_strjoin(path, root->left->list->value);
		args = list_to_array(root->left->list);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (execve(path_name, args, NULL) == -1)
			exit(1);
	}
	close(fd[1]);
	// if(root->list->last == 1)
	// 	wait_forks(forks, pos);
	*pos = *pos + 1;
	if (root->right->list->type >= IN_REDIR && root->right->list->type <= DOUB_QUOTE)
	{
		forks[*pos][0] = fork();
		if (forks[*pos][0] == -1)
			exit(1);
		else if (forks[*pos][0] == 0)
		{
			path_name = ft_strjoin(path, root->right->list->value);
			args = list_to_array(root->right->list);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			if (execve(path_name, args, NULL) == -1)
				exit(1);
		}
		close(fd[0]);
		if(root->right->list->last == 1)
			wait_forks(forks, pos);
		*pos = *pos + 1;
	}
	else
		root->right->pipe_read = fd[0];
	// to do: if last pipe, wait for all processes
}

void wait_forks(int **forks, int pos)
{
	int i;
	int status;

	i = 0;
	while(i < pos)
	{
		waitpid(forks[i][0], &status, NULL);
		i++;
	}
}