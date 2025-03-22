/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_piping.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:58:05 by tomsato           #+#    #+#             */
/*   Updated: 2025/03/23 00:21:06 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	recursive_piping(int current_index, int ac, char **av, char **envp)
{
	int		fd;
	int		pipefd[2];
	pid_t	cpid;
	char	**execve_argv;
	char	*full_path;

	if (current_index == 1)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
			exit_with_error("open infile");
		if (dup2(fd, STDIN_FILENO) < 0)
			exit_with_error("dup2 infile");
		close(fd);
		execve_argv = get_execve_argv(av, 2);
		full_path = find_command_path(execve_argv[0], envp);
		printf("%s\n", full_path);
		if (execve(full_path, execve_argv, envp) == -1)
			exit_with_error("execve at index 1");
		return (0);
	}
	else if (current_index == ac - 1)
	{
		fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			exit_with_error("open outfile");
		if (dup2(fd, STDOUT_FILENO) < 0)
			exit_with_error("dup2 outfile");
		recursive_piping(current_index - 1, ac, av, envp);
		close(fd);
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (pipe(pipefd) == -1)
			exit_with_error("pipe");
		cpid = fork();
		if (cpid == -1)
			exit_with_error("fork");
		if (cpid == 0)
		{
			close(pipefd[0]);
			if (dup2(pipefd[1], STDOUT_FILENO) < 0)
				exit_with_error("dup2 in child");
			close(pipefd[1]);
			recursive_piping(current_index - 1, ac, av, envp);
		}
		else
		{
			waitpid(cpid, NULL, 0);
			close(pipefd[1]);
			if (dup2(pipefd[0], STDIN_FILENO) < 0)
				exit_with_error("dup2 in parent");
			close(pipefd[0]);
			execve_argv = get_execve_argv(av, current_index);
			full_path = find_command_path(execve_argv[0], envp);
			printf("%s\n", full_path);
			if (execve(full_path, execve_argv, envp) == -1)
				exit_with_error("execve");
		}
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	if (ac < 5)
	{
		printf("Usage: %s infile cmd1 cmd2 outfile\n", av[0]);
		return (1);
	}
	recursive_piping(ac - 1, ac, av, envp);
	return (0);
}
