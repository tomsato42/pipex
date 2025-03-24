/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 00:21:51 by tomsato           #+#    #+#             */
/*   Updated: 2025/03/25 02:25:08 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	execute_command(char **av, int index, char **envp)
{
	char	*full_path;
	char	**execve_argv;

	execve_argv = get_execve_argv(av, index);
	if (!execve_argv)
		exit_with_error("get_execve_argv");
	full_path = find_command_path(execve_argv[0], envp);
	if (!full_path)
	{
		ft_free_split(execve_argv);
		exit_with_error("command not found");
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
