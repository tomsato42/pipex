/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_piping.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:58:05 by tomsato           #+#    #+#             */
/*   Updated: 2025/03/26 18:13:01 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	rec_safe_dup2(int oldfd, int newfd, const char *error_message)
{
	if (dup2(oldfd, newfd) < 0)
	{
		perror(error_message);
		exit(EXIT_FAILURE);
	}
}

static int	rec_handle_infile(char **av, char **envp)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		exit_with_error("open infile");
	rec_safe_dup2(fd, STDIN_FILENO, "dup2 infile");
	close(fd);
	execute_command(av, 2, envp);
	return (0);
}

static int	rec_handle_outfile(int current_index, int ac, char **av,
		char **envp)
{
	int	fd;

	fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit_with_error("open outfile");
	rec_safe_dup2(fd, STDOUT_FILENO, "dup2 outfile");
	recursive_piping(current_index - 1, ac, av, envp);
	close(fd);
	return (0);
}

static int	rec_handle_pipe(int current_index, int ac, char **av, char **envp)
{
	int		pipefd[2];
	pid_t	cpid;

	if (pipe(pipefd) == -1)
		exit_with_error("pipe");
	cpid = fork();
	if (cpid == -1)
		exit_with_error("fork");
	if (cpid == 0)
	{
		close(pipefd[0]);
		rec_safe_dup2(pipefd[1], STDOUT_FILENO, "dup2 in child");
		close(pipefd[1]);
		recursive_piping(current_index - 1, ac, av, envp);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipefd[1]);
		rec_safe_dup2(pipefd[0], STDIN_FILENO, "dup2 in parent");
		close(pipefd[0]);
		execute_command(av, current_index, envp);
	}
	return (0);
}

int	recursive_piping(int current_index, int ac, char **av, char **envp)
{
	if (current_index == 2)
		rec_handle_infile(av, envp);
	else if (current_index == ac - 1)
		rec_handle_outfile(current_index, ac, av, envp);
	else if (current_index == 3 && ft_strncmp(av[1], "here_doc", 10) == 0)
	{
		handle_here_doc(av[2]);
		execute_command(av, 3, envp);
	}
	else
		rec_handle_pipe(current_index, ac, av, envp);
	return (0);
}
