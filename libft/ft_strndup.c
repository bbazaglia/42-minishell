/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:37:13 by cogata            #+#    #+#             */
/*   Updated: 2024/03/21 13:45:16 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *s, size_t n)
{
	char	*dest;
	int		i;

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
