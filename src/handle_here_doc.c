/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 00:47:49 by tomsato           #+#    #+#             */
/*   Updated: 2025/03/25 00:49:55 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../get_next_line/get_next_line.h"

static void	handle_here_doc_loop(int pipefd[2], char *limitter)
{
	char	*line;
	size_t	len;

	write(STDERR_FILENO, "heredoc> ", 10);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		len = ft_strlen(line);
		if (0 < len && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (ft_strncmp(line, limitter, len) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
		write(STDERR_FILENO, "heredoc> ", 10);
	}
}

void	handle_here_doc(char *limitter)
{
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		exit_with_error("pipe");
	handle_here_doc_loop(pipefd, limitter);
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
		exit_with_error("dup2");
	close(pipefd[1]);
	close(pipefd[0]);
}
