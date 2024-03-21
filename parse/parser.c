/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:45:32 by cogata            #+#    #+#             */
/*   Updated: 2024/03/21 16:17:48 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parse(char *input, t_tree **root)
{
	t_node	*head;

	head = tokenizer(input);
	if (check_syntax(head))
		return ;
	check_heredoc(head);
	build_tree(root, head);
}
