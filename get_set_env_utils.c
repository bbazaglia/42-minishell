/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:02:09 by cogata            #+#    #+#             */
/*   Updated: 2024/03/07 16:02:11 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

char	**get_env_table(void)
{
	int		i;
	char	**env_table;

	i = 0;
	while (__environ[i])
		i++;
	env_table = malloc(sizeof(char *) * (i + 1));
	if (env_table == NULL)
		error(MALLOC_FAILED);
	i = 0;
	while (__environ[i])
	{
		env_table[i] = ft_strdup(__environ[i]);
		i++;
	}
	env_table[i] = NULL;
	return (env_table);
}

void	free_env_table(char **env_table)
{
	int	i;

	i = 0;
	while (env_table[i])
	{
		free(env_table[i]);
		i++;
	}
	free(env_table);
}
