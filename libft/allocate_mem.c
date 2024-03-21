/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_mem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:57:04 by bbazagli          #+#    #+#             */
/*   Updated: 2024/03/21 17:14:42 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	**get_mem_address(void)
{
	static t_list	*ptr;

	return (&ptr);
}

void	collect_mem(void *content)
{
	ft_lstadd_back(get_mem_address(), ft_lstnew(content));
}

void	*allocate_mem(size_t nmemb, size_t size)
{
	void	*content;

	content = ft_calloc(nmemb, size);
	collect_mem(content);
	return (content);
}
