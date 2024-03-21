/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:59:09 by bbazagli          #+#    #+#             */
/*   Updated: 2024/03/21 17:31:53 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_mem(t_list **list)
{
	t_list	*cur;

	while (*list)
	{
		cur = (*list)->next;
		free((*list)->content);
		free(*list);
		*list = cur;
	}
}
