/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:33:08 by cogata            #+#    #+#             */
/*   Updated: 2024/03/08 12:11:40 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

volatile int g_heredoc_signal;

int main(void)
{
	int fd;
	char *prompt;
	t_node *head;
	struct termios term;

	head = NULL;
	fd = dup(STDIN_FILENO);
	tcgetattr(STDIN_FILENO, &term);
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
		g_heredoc_signal = 0;
	}
	return (0);
}