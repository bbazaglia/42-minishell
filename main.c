/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:33:08 by cogata            #+#    #+#             */
/*   Updated: 2024/03/05 14:33:11 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	main(void)
{
	char	*prompt;
	t_node	*head;

	head = NULL;
	while (1)
	{
		prompt = readline("minishell: ");
		if (!prompt)
			exit(printf("exit\n"));
		if (ft_strlen(prompt))
			add_history(prompt);
		head = tokenizer(prompt);
		check_syntax(head);
		check_heredoc(head);
	}
	return (0);
}
