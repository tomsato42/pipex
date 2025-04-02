/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 00:21:51 by tomsato           #+#    #+#             */
/*   Updated: 2025/04/02 23:01:20 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	check_all_space(char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

static void	execute_direct_path(char **execve_argv, char **envp)
{
	if (execve(execve_argv[0], execve_argv, envp) == -1)
		exit_with_error("execve");
}

static void	execute_with_path(char **execve_argv, char **envp)
{
	char	*full_path;

	full_path = find_command_path(execve_argv[0], envp);
	if (!full_path || check_all_space(execve_argv[0]))
	{
		ft_putstr_fd(execve_argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_free_split(execve_argv);
		exit(127);
	}
	if (execve(full_path, execve_argv, envp) == -1)
	{
		free(full_path);
		ft_free_split(execve_argv);
		exit_with_error("execve");
	}
	free(full_path);
	ft_free_split(execve_argv);
}

void	execute_command(char **av, int index, char **envp)
{
	char	**execve_argv;

	execve_argv = get_execve_argv(av, index);
	if (!execve_argv)
		exit_with_error("get_execve_argv");
	if (access(execve_argv[0], X_OK) == 0)
		execute_direct_path(execve_argv, envp);
	else
		execute_with_path(execve_argv, envp);
}
