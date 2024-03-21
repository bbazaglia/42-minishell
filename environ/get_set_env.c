/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:12:59 by cogata            #+#    #+#             */
/*   Updated: 2024/03/21 14:03:00 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**insert_env_var(char **env_table, char *key, char *value)
{
	char	*var;
	char	*var_new_line;
	char	*var_old_line;

	var = ft_strjoin(key, "=");
	var_new_line = ft_strjoin(var, value);
	var_old_line = ft_strjoin(var, getenv(key));
	free(var);
	if (getenv(key))
		env_table = modify_env_var(env_table, var_new_line, var_old_line);
	else
		env_table = add_env_var(env_table, var_new_line);
	free(var_new_line);
	free(var_old_line);
	__environ = env_table;
	return (env_table);
}

char	**modify_env_var(char **env_table, char *var_new_line,
		char *var_old_line)
{
	int	i;

	i = 0;
	while (env_table[i])
	{
		if (ft_strncmp(env_table[i], var_old_line,
				ft_strlen(env_table[i])) == 0)
		{
			free(env_table[i]);
			env_table[i] = ft_strdup(var_new_line);
			break ;
		}
		i++;
	}
	return (env_table);
}

char	**add_env_var(char **env_table, char *var_line)
{
	int		i;
	int		size;
	char	**temp;

	temp = env_table;
	size = 0;
	while (env_table[size])
		size++;
	env_table = malloc(sizeof(char *) * (size + 2));
	if (env_table == NULL)
		error(MALLOC_FAILED);
	i = 0;
	while (__environ[i])
	{
		env_table[i] = ft_strdup(__environ[i]);
		i++;
	}
	env_table[i++] = ft_strdup(var_line);
	env_table[i] = NULL;
	free_env_table(temp);
	return (env_table);
}

char	**del_env_var(char **env_table, char *key)
{
	int		size;
	char	*var_equal;
	char	*var_line;
	char	**temp;

	if (!getenv(key))
		return (env_table);
	var_equal = ft_strjoin(key, "=");
	var_line = ft_strjoin(var_equal, getenv(key));
	free(var_equal);
	size = 0;
	while (env_table[size])
		size++;
	temp = env_table;
	env_table = update_env_table(var_line, size);
	free(var_line);
	free_env_table(temp);
	__environ = env_table;
	return (env_table);
}

char	**update_env_table(char *var_line, int size)
{
	int		i;
	int		j;
	char	**env_table;

	env_table = malloc(sizeof(char *) * size);
	if (env_table == NULL)
		error(MALLOC_FAILED);
	i = 0;
	j = 0;
	while (__environ[i])
	{
		if (ft_strncmp(__environ[i], var_line, ft_strlen(__environ[i])) == 0)
			i++;
		if (!__environ[i])
			break ;
		env_table[j] = ft_strdup(__environ[i]);
		i++;
		j++;
	}
	env_table[j] = NULL;
	return (env_table);
}
