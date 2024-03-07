/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:30:55 by cogata            #+#    #+#             */
/*   Updated: 2024/03/07 12:41:06 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	error(int err)
{
	if (err == SYNTAX_ERROR)
		ft_putstr_fd("syntax error\n", 2);
	else if (err == FD_ERROR)
		ft_putstr_fd("file descriptor error\n", 2);
	exit(EXIT_FAILURE);
}
