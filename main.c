/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:33:08 by cogata            #+#    #+#             */
/*   Updated: 2024/03/25 11:34:54 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

volatile int	g_signal;

char	*init_read(void)
{
	char	*input;

	g_signal = 0;
	initialize_signals();
	input = readline("minishell (◕‿◕) > ");
	if (!input && g_signal == 0)
		exit(printf("exit\n"));
	return (input);
}

int	main(void)
{
	int				fd;
	char			*input;
	struct termios	term;
	t_tree			*root;

	root = NULL;
	fd = dup(STDIN_FILENO);
	tcgetattr(STDIN_FILENO, &term);
	while (1)
	{
		input = init_read();
		if (!ft_strlen(input))
			continue ;
		add_history(input);
		parse(input, &root);
		printTree(root);
		// execute(root);
		dup2(fd, STDIN_FILENO);
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
	return (0);
}
