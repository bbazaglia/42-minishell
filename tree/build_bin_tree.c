/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_bin_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:48:26 by bbazagli          #+#    #+#             */
/*   Updated: 2024/03/21 11:55:30 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	t_node	**ptr_list;

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
