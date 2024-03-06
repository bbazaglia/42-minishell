/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:12:59 by cogata            #+#    #+#             */
/*   Updated: 2024/03/06 17:13:00 by cogata           ###   ########.fr       */
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
	i = 0;
	while (__environ[i])
	{
		env_table[i] = ft_strdup(__environ[i]);
		i++;
	}
	env_table[i] = NULL;
	return (env_table);
}

void	add_env_var(char **env_table, char *var_line)
{
	int	i;

	i = 0;
	while (env_table[i])
	{
		free(env_table[i]);
		i++;
	}
	free(env_table);
	while (__environ[i])
		i++;
	env_table = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (__environ[i])
	{
		env_table[i] = ft_strdup(__environ[i]);
		i++;
	}
	env_table[i++] = ft_strdup(var_line);
	env_table[i] = NULL;
	__environ = env_table;
}
