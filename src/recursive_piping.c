/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_piping.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:58:05 by tomsato           #+#    #+#             */
/*   Updated: 2025/03/25 03:28:51 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	safe_dup2(int oldfd, int newfd, const char *error_message)
{
	if (dup2(oldfd, newfd) < 0)
	{
		perror(error_message);
		exit(EXIT_FAILURE);
	}
}

static int	handle_infile(char **av, char **envp)
{
	int		fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		exit_with_error("open infile");
	safe_dup2(fd, STDIN_FILENO, "dup2 infile");
	close(fd);
	execute_command(av, 2, envp);
	return (0);
}

static int	handle_outfile(int current_index, int ac, char **av, char **envp)
{
	int	fd;

	fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit_with_error("open outfile");
	safe_dup2(fd, STDOUT_FILENO, "dup2 outfile");
	recursive_piping(current_index - 1, ac, av, envp);
	close(fd);
	exit(EXIT_SUCCESS);
}

static int	handle_pipe(int current_index, int ac, char **av, char **envp)
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
		safe_dup2(pipefd[1], STDOUT_FILENO, "dup2 in child");
		close(pipefd[1]);
		recursive_piping(current_index - 1, ac, av, envp);
	}
	else
	{
		close(pipefd[1]);
		safe_dup2(pipefd[0], STDIN_FILENO, "dup2 in parent");
		close(pipefd[0]);
		execute_command(av, current_index, envp);
	}
	exit(EXIT_SUCCESS);
}

int	recursive_piping(int current_index, int ac, char **av, char **envp)
{
	if (current_index == 2)
		handle_infile(av, envp);
	else if (current_index == ac - 1)
		handle_outfile(current_index, ac, av, envp);
	else if (current_index == 3 && ft_strncmp(av[1], "here_doc", 10) == 0)
	{
		handle_here_doc(av[2]);
		execute_command(av, 3, envp);
	}
	else
		handle_pipe(current_index, ac, av, envp);
	return (0);
}
