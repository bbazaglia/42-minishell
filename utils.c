/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:30:59 by cogata            #+#    #+#             */
/*   Updated: 2024/03/21 17:06:10 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	error(int err)
{
	if (err == SYNTAX_ERROR)
		ft_putstr_fd("Syntax error\n", 2);
	else if (err == MALLOC_FAILED)
		ft_putstr_fd("Memory allocation failed\n", 2);
	else if (err == SIGNAL_ERROR)
		ft_putstr_fd("Error setting up signal handler\n", 2);
	free_mem(get_mem_address());
	return (1);
}

void	print_lst_node(t_node **head)
{
	int		i;
	t_node	*temp;

	i = 0;
	temp = *head;
	while (temp)
	{
		printf("node %d\n", i);
		printf("value: %s\n", temp->value);
		printf("type: %d\n", temp->type);
		printf("next_char: %c\n\n", temp->next_char);
		temp = temp->next;
		i++;
	}
}
