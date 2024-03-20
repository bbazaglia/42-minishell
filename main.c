/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:33:08 by cogata            #+#    #+#             */
/*   Updated: 2024/03/20 11:42:18 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

volatile int	g_signal;

int	main(void)
{
	int fd;
	char *input;
	t_node *head;
	struct termios term;
	t_tree *root;

	root = NULL;
	head = NULL;
	fd = dup(STDIN_FILENO);
	tcgetattr(STDIN_FILENO, &term);
	while (1)
	{
		initialize_signals();
		input = readline("minishell (◕‿◕) > ");
		if (!input && g_signal == 0)
			exit(printf("exit\n"));
		if (ft_strlen(input))
		{
			add_history(input);
			head = tokenizer(input);
			check_syntax(head);
			check_heredoc(head);
			build_tree(&root, head);
			// printTree(root);
			execute(root);
			dup2(fd, STDIN_FILENO);
		}
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		g_signal = 0;
	}
	return (0);
}