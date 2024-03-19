/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:15:20 by bbazagli          #+#    #+#             */
/*   Updated: 2024/03/19 18:55:08 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	initialize_signals(void)
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR || signal(SIGQUIT,
			SIG_IGN) == SIG_ERR)
		error(SIGNAL_ERROR);
}

void	sigint_handler(int signo)
{
	// printf("Cheguei no Ctrl C");
	(void)signo;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_heredoc_signal = 0;
}

void	heredoc_handler(int signo)
{
	(void)signo;
	write(STDOUT_FILENO, "\n", 1);
	close(STDIN_FILENO);
	g_heredoc_signal = 1;
}
