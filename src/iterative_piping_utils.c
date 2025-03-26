/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterative_piping_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:09:03 by tomsato           #+#    #+#             */
/*   Updated: 2025/03/26 18:09:29 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	safe_dup2(int oldfd, int newfd, const char *error_message)
{
	if (dup2(oldfd, newfd) < 0)
	{
		perror(error_message);
		exit(EXIT_FAILURE);
	}
}

void	setup_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
		exit_with_error("pipe");
}

void	handle_outfile(char **av, int ac, char **envp, int prev_pipe_read)
{
	int	outfile_fd;

	outfile_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
		exit_with_error("open outfile");
	safe_dup2(prev_pipe_read, STDIN_FILENO, "dup2 stdin");
	safe_dup2(outfile_fd, STDOUT_FILENO, "dup2 stdout");
	close(prev_pipe_read);
	close(outfile_fd);
	execute_command(av, ac - 2, envp);
	exit(EXIT_SUCCESS);
}

pid_t	create_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit_with_error("fork");
	return (pid);
}

void	setup_child_io(int prev_pipe, int pipe_fd[2])
{
	close(pipe_fd[0]);
	safe_dup2(prev_pipe, STDIN_FILENO, "dup2 stdin");
	safe_dup2(pipe_fd[1], STDOUT_FILENO, "dup2 stdout");
	close(prev_pipe);
	close(pipe_fd[1]);
}
