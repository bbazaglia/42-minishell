/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:30:59 by cogata            #+#    #+#             */
/*   Updated: 2024/03/04 12:31:00 by cogata           ###   ########.fr       */
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

void	print_ptr_list(t_node **head)
{
	int		i;

	i = 0;
	while(head[i])
	{	
		printf("################\n");
		printf("HEAD %d\n", i);
		print_lst_node(&head[i]);
		printf("################\n");
		i++;
	}
}

char	*ft_strndup(char *s, size_t n)
{
	int		i;
	char	*dest;

	dest = malloc(n + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (n != 0 && s[i])
	{
		dest[i] = s[i];
		i++;
		n--;
	}
	dest[i] = '\0';
	return (dest);
}
