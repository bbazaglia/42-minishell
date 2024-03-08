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

int	main(void)
{
	char			*prompt;
	t_node			*head;
	struct termios	term;

	head = NULL;
	tcgetattr(STDIN_FILENO, &term);
	while (1)
	{
		initialize_signals();
		set_terminal_attributes();
		prompt = readline("minishell: ");
		if (!prompt)
			exit(printf("exit\n"));
		if (ft_strlen(prompt))
			add_history(prompt);
		head = tokenizer(prompt);
		check_syntax(head);
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
	return (0);
}
