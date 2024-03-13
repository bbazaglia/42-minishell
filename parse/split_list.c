#include "../include/minishell.h"

void	split_list(t_node *head)
{
	int		i;
	t_node	*tmp;
	t_node	*tmp2;
	t_node	**ptr_list;
	int		count_ptr;
	int		count_pipe;

	tmp = head;
	count_ptr = 0;
	count_pipe = 0;
	while (tmp)
	{
		if (tmp->type == PIPE || tmp->type == AND || tmp->type == OR)
		{
			if (tmp->type == PIPE)
				count_pipe++;
			count_ptr++;
		}
		tmp = tmp->next;
	}
	count_ptr = (count_ptr * 2) + 1;
	ptr_list = ft_calloc(sizeof(t_node), count_ptr);
	i = 0;
	tmp = head;
	while (tmp)
	{
		if (tmp->type != PIPE && tmp->type != AND && tmp->type != OR)
		{
			ptr_list[i] = tmp;
			while (tmp->next && tmp->next->type != PIPE
				&& tmp->next->type != AND && tmp->next->type != OR)
				tmp = tmp->next;
			tmp2 = tmp->next;
			tmp->next = NULL;
		}
		else
		{
			ptr_list[i] = tmp;
			tmp2 = tmp->next;
			tmp->next = NULL;
		}
		tmp = tmp2;
		i++;
	}
	// print_ptr_list(ptr_list);
	execute(ptr_list, count_pipe);
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

void	execute(t_node **ptr_list, int count_pipe)
{
	int i;
	int **fds;
	int pos;
	char *path_name;
	char *path = "/usr/bin/";
	char **args;
	int fork_id;

	//Mar 13
	int status;
	int **forks;
	int index;
	int j;
	status = 0;
	index = 0;

	fds = malloc(sizeof(int *) * count_pipe);
	i = 0;
	while (i < count_pipe)
	{
		fds[i] = malloc(sizeof(int) * 2);
		i++;
	}

	//Mar 13
	i = 0;
	forks = malloc(sizeof(int *) * (count_pipe + 1));
	while (i < (count_pipe + 1))
	{
		forks[i] = malloc(sizeof(int));
		i++;
	}

	i = 0;
	pos = 0;
	while (ptr_list[i])
	{
		if (i > 0 && ptr_list[i + 1] && ptr_list[i - 1]->type == PIPE
			&& ptr_list[i + 1]->type == PIPE)
		{
			if (pipe(fds[pos]) == -1)
				exit(1);
			forks[index][0] = fork();
			if (forks[index][0] == -1)
				exit(1);
			else if (forks[index][0] == 0)
			{
				path_name = ft_strjoin(path, ptr_list[i]->value);
				args = list_to_array(ptr_list[i]);
				if (dup2(fds[pos - 1][0], STDIN_FILENO) == -1)
					exit(1);
				if (dup2(fds[pos][1], STDOUT_FILENO) == -1)
					exit(1);
				close(fds[pos][0]);
				close(fds[pos - 1][0]);
				close(fds[pos][1]);
				if (execve(path_name, args, NULL) == -1)
					exit(EXIT_FAILURE);
			}
			close(fds[pos - 1][0]);
			close(fds[pos][1]);
			pos++;
			index++;
		}
		else if (ptr_list[i + 1] && ptr_list[i + 1]->type == PIPE)
		{
			if (pipe(fds[pos]) == -1)
				exit(1);
			forks[index][0] = fork();
			if (forks[index][0] == -1)
				exit(1);
			else if (forks[index][0] == 0)
			{
				path_name = ft_strjoin(path, ptr_list[i]->value);
				args = list_to_array(ptr_list[i]);
				dup2(fds[pos][1], STDOUT_FILENO);
				close(fds[pos][1]);
				close(fds[pos][0]);
				if (execve(path_name, args, NULL) == -1)
					exit(EXIT_FAILURE);
			}
			close(fds[pos][1]);
			pos++;
			index++;
		}
		else if (i > 0 && ptr_list[i - 1]->type == PIPE)
		{
			forks[index][0] = fork();
			if (forks[index][0] == -1)
				exit(1);
			else if (forks[index][0] == 0)
			{
				path_name = ft_strjoin(path, ptr_list[i]->value);
				args = list_to_array(ptr_list[i]);
				dup2(fds[pos - 1][0], STDIN_FILENO);
				close(fds[pos - 1][0]);
				if (execve(path_name, args, NULL) == -1)
					exit(EXIT_FAILURE);
			}
			close(fds[pos - 1][0]);
			j = 0;
			while (j < (count_pipe + 1))
			{
				waitpid(forks[j][0], &status, 0);
				j++;
			}
			index++;
		}
		else if (ptr_list[i]->type == AND)
		{
			i++;
			if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
			{
				fork_id = fork();
				if (fork_id < 0)
					exit(1);
				else if (fork_id == 0)
				{
					path_name = ft_strjoin(path, ptr_list[i]->value);
					args = list_to_array(ptr_list[i]);
					if (execve(path_name, args, NULL) == -1)
						exit(EXIT_FAILURE);
				}
				waitpid(fork_id, &status, 0);
			}
			else
				printf("Error in &&\n");
		}
		else if (ptr_list[i]->type == OR)
		{
			i++;
			if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			{
				fork_id = fork();
				if (fork_id < 0)
					exit(1);
				else if (fork_id == 0)
				{
					path_name = ft_strjoin(path, ptr_list[i]->value);
					args = list_to_array(ptr_list[i]);
					if (execve(path_name, args, NULL) == -1)
						exit(EXIT_FAILURE);
				}
				waitpid(fork_id, &status, 0);
			}
			else
				printf("Error in ||\n");
		}
		else
		{
			fork_id = fork();
			if (fork_id < 0)
				exit(1);
			else if (fork_id == 0)
			{
				path_name = ft_strjoin(path, ptr_list[i]->value);
				args = list_to_array(ptr_list[i]);
				if (execve(path_name, args, NULL) == -1)
					exit(EXIT_FAILURE);
			}
			waitpid(fork_id, &status, 0);
		}
		i++;
	}
}