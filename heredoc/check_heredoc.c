/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:15:35 by bbazagli          #+#    #+#             */
/*   Updated: 2024/03/20 16:27:10 by cogata           ###   ########.fr       */
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

void	check_delimiter(t_node *head, char *heredoc_input, char *delimiter)
{
	char	*temp;

	while (ft_strncmp(heredoc_input, delimiter, ft_strlen(delimiter)) != 0)
	{
		temp = heredoc_input;
		heredoc_input = ft_strjoin(temp, "\n");
		free(temp);
		write(head->fd, heredoc_input, ft_strlen(heredoc_input));
		free(heredoc_input);
		heredoc_input = readline("> ");
		if (!heredoc_input)
		{
			if (g_signal == 0)
				printf("warning: here-document at line 1 delimited by end-of-file\n");
			break ;
		}
	}
	free(heredoc_input);
}

void	check_heredoc(t_node *head)
{
	char	*heredoc_input;
	char	*delimiter;

	while (head->next)
	{
		if (head->type == HEREDOC)
		{
			signal(SIGINT, sigint_cmd_handler);
			delimiter = ft_strtrim(head->next->value, "'\"");
			head->fd = create_heredoc_temp();
			heredoc_input = readline("> ");
			if (!heredoc_input)
			{
				if (g_signal == 0)
					printf("warning: here-document at line 1 delimited by end-of-file\n");
				break ;
			}
			check_delimiter(head, heredoc_input, delimiter);
		}
		head = head->next;
	}
	free(delimiter);
}
