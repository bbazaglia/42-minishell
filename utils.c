/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:30:59 by cogata            #+#    #+#             */
/*   Updated: 2024/03/20 14:38:12 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

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
