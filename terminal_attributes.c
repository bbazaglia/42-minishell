/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_attributes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:34:41 by bbazagli          #+#    #+#             */
/*   Updated: 2024/03/08 10:57:52 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

// to do: tcsetattr will be called when the exit status equals to SIGQUIT

void	set_terminal_attributes(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
}
