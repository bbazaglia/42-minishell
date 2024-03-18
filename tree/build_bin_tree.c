
#include "../include/minishell.h"

int	**allocate_forks(int count_fork)
{
	int	pos;
	int	**forks;

	pos = 0;
	forks = ft_calloc(sizeof(int *), count_fork);
	while (pos < count_fork)
	{
		forks[pos] = ft_calloc(sizeof(int), 1);
		pos++;
	}
	return (forks);
}

void	count_processes(t_tree *root, int *count_fork)
{
	if (root->left)
		count_processes(root->left, count_fork);
	if (root->list->type >= IN_REDIR && root->list->type <= DOUB_QUOTE)
		*count_fork = *count_fork + 1;
	if (root->right)
		count_processes(root->right, count_fork);
}

t_node	**split_list(t_node *list)
{
	int		i;
	int		found;
	t_node	*tmp;
	t_node	*tmp2;
	t_node	**ptr_list;

	i = 0;
	found = 0;
	tmp = list;
	while (tmp)
	{
		if (tmp->type == AND || tmp->type == OR)
		{
			found = 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (found == 0)
	{
		tmp = list;
		while (tmp)
		{
			if (tmp->type == PIPE)
			{
				found = 2;
				break ;
			}
			tmp = tmp->next;
		}
	}
	if (found == 0)
		return (NULL);
	ptr_list = malloc(sizeof(t_node *) * 3);
	i = 0;
	tmp = list;
	if (found == 1)
	{
		found = 0;
		while (tmp)
		{
			if (found == 0 && (tmp->type == AND || tmp->type == OR))
			{
				found = 1;
				ptr_list[i] = tmp;
				tmp2 = tmp->next;
				tmp->next = NULL;
			}
			else
			{
				ptr_list[i] = tmp;
				while ((found == 1 && tmp->next) || (tmp->next
						&& tmp->next->type != AND && tmp->next->type != OR))
					tmp = tmp->next;
				tmp2 = tmp->next;
				tmp->next = NULL;
			}
			tmp = tmp2;
			i++;
		}
	}
	else if (found == 2)
	{
		found = 0;
		while (tmp)
		{
			if (found == 0 && tmp->type == PIPE)
			{
				found = 1;
				ptr_list[i] = tmp;
				tmp2 = tmp->next;
				tmp->next = NULL;
			}
			else
			{
				ptr_list[i] = tmp;
				while ((found == 1 && tmp->next) || (tmp->next
						&& tmp->next->type != PIPE))
					tmp = tmp->next;
				tmp2 = tmp->next;
				tmp->next = NULL;
			}
			tmp = tmp2;
			i++;
		}
	}
	return (ptr_list);
}

void	create_node(t_node *list, t_tree **root)
{
	*root = malloc(sizeof(t_tree));
	(*root)->list = list;
	(*root)->right = NULL;
	(*root)->left = NULL;
	(*root)->pipe_read = -1;
}

void	build_tree(t_tree **root, t_node *list)
{
	t_node **ptr_list;

	ptr_list = split_list(list);
	if (!ptr_list && list)
		return (create_node(list, root));
	if (ptr_list[1])
		create_node(ptr_list[1], root);
	if (ptr_list[0])
		build_tree(&(*root)->left, ptr_list[0]);
	if (ptr_list[2])
		build_tree(&(*root)->right, ptr_list[2]);
	else
		return ;
}