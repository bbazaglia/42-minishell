/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:15:35 by bbazagli          #+#    #+#             */
/*   Updated: 2024/03/04 16:16:02 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	create_heredoc_temp(void)
{
	static int	num;
	int			fd;
	char		*filename;
	char		*temp_path;

	filename = ft_itoa(num);
	temp_path = ft_strjoin("/tmp/.heredoc_", filename);
	fd = open(temp_path, O_CREAT | O_RDWR | O_TRUNC, 0666);
	num++;
	free(filename);
	free(temp_path);
	return (fd);
}

void	check_heredoc(t_node *head)
{
	char	*heredoc_prompt;
	char	*delimiter;
	char	*temp;

	while (head->next)
	{
		if (head->type == HEREDOC)
		{
			signal(SIGINT, heredoc_handler);
			delimiter = ft_strtrim(head->next->value, "'\"");
			head->fd = create_heredoc_temp();
			heredoc_prompt = readline("> ");
			if (!heredoc_prompt)
			{
				free(delimiter);
				if (g_heredoc_signal == 0)
					printf("warning: here-document at line 1 delimited by end-of-file\n");
				break ;
			}
			while (ft_strncmp(heredoc_prompt, delimiter,
					ft_strlen(delimiter)) != 0)
			{
				temp = heredoc_prompt;
				heredoc_prompt = ft_strjoin(temp, "\n");
				free(temp);
				write(head->fd, heredoc_prompt, ft_strlen(heredoc_prompt));
				heredoc_prompt = readline("> ");
				if (!heredoc_prompt)
				{
					free(delimiter);
					if (g_heredoc_signal == 0)
						printf("warning: here-document at line 1 delimited by end-of-file\n");
					break ;
				}
			}
			free(delimiter);
		}
		head = head->next;
	}
}
