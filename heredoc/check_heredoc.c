/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:15:35 by bbazagli          #+#    #+#             */
/*   Updated: 2024/03/07 12:42:52 by bbazagli         ###   ########.fr       */
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
	if (fd < 0)
		error(FD_ERROR);
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
			delimiter = ft_strtrim(head->next->value, "'\"");
			head->fd = create_heredoc_temp();
			heredoc_prompt = readline("> ");
			while (ft_strncmp(heredoc_prompt, delimiter,
					ft_strlen(delimiter)) != 0)
			{
				temp = heredoc_prompt;
				heredoc_prompt = ft_strjoin(temp, "\n");
				free(temp);
				write(head->fd, heredoc_prompt, ft_strlen(heredoc_prompt));
				heredoc_prompt = readline("> ");
			}
			free(delimiter);
		}
		head = head->next;
	}
}
