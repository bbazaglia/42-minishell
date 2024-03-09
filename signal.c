/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:15:20 by bbazagli          #+#    #+#             */
/*   Updated: 2024/03/08 10:51:47 by bbazagli         ###   ########.fr       */
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

/*
After sending a CTRL C in a heredoc, the program is correctly returning to the loop.
However, when I send a CTRL C, the program is incorrectly skipping one line.

minishell: << oi
> ^C
minishell: ^C

minishell:

This is how my code looks like now after the changes:
void	sigint_handler(int signo)
{
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

volatile int g_heredoc_signal;

int main(void)
{
	char *prompt;
	t_node *head;
	struct termios term;

	head = NULL;
	tcgetattr(STDIN_FILENO, &term);

	int fd;

	fd = dup(STDIN_FILENO);
	while (1)
	{
		initialize_signals();
		prompt = readline("minishell: ");
		if (!prompt && g_heredoc_signal == 0)
			exit(printf("exit\n"));
		if (!ft_strlen(prompt))
			continue;
		add_history(prompt);
		head = tokenizer(prompt);
		check_syntax(head);
		check_heredoc(head);
		dup2(fd, STDIN_FILENO);
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		if (g_heredoc_signal == 1)
			close(head->fd); 
	}
	return (0);
}

*/