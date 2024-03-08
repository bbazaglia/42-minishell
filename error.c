/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:30:55 by cogata            #+#    #+#             */
/*   Updated: 2024/03/04 18:12:57 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	error(int err)
{
	if (err == SYNTAX_ERROR)
		ft_putstr_fd("Syntax error\n", 2);
	else if (err == MALLOC_FAILED)
		ft_putstr_fd("Memory allocation failed\n", 2);
	exit(EXIT_FAILURE);
}
