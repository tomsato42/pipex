/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_here_doc_iterative.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:06:34 by tomsato           #+#    #+#             */
/*   Updated: 2025/03/26 18:08:16 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	setup_here_doc_io(int prev_pipe, int pipe_fd[2], int is_last)
{
	close(pipe_fd[0]);
	safe_dup2(prev_pipe, STDIN_FILENO, "dup2 stdin");
	if (!is_last)
		safe_dup2(pipe_fd[1], STDOUT_FILENO, "dup2 stdout");
	if (prev_pipe != STDIN_FILENO)
		close(prev_pipe);
	close(pipe_fd[1]);
}

void	setup_here_doc_out(char **av, int ac)
{
	int	outfile;

	outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile == -1)
		exit_with_error("open outfile");
	safe_dup2(outfile, STDOUT_FILENO, "dup2 stdout");
	close(outfile);
}

void	process_here_doc_child(char **av, char **envp, int ac, int i)
{
	int	is_last;

	is_last = (i == ac - 2);
	if (is_last)
		setup_here_doc_out(av, ac);
	execute_command(av, i, envp);
	exit(EXIT_SUCCESS);
}

void	process_here_doc_cmds(char **av, char **envp, int ac, int i)
{
	int		pipe_fd[2];
	int		prev_pipe;
	pid_t	pid;
	int		is_last;

	i = 3;
	prev_pipe = STDIN_FILENO;
	while (i < ac - 1)
	{
		is_last = (i == ac - 2);
		setup_pipe(pipe_fd);
		pid = create_fork();
		if (pid == 0)
		{
			setup_here_doc_io(prev_pipe, pipe_fd, is_last);
			process_here_doc_child(av, envp, ac, i);
		}
		if (prev_pipe != STDIN_FILENO)
			close(prev_pipe);
		close(pipe_fd[1]);
		prev_pipe = pipe_fd[0];
		i++;
	}
	close(prev_pipe);
}

int	handle_here_doc_iterative(char **av, char **envp, int ac)
{
	if (ft_strncmp(av[1], "here_doc", 10) == 0)
	{
		handle_here_doc(av[2]);
		process_here_doc_cmds(av, envp, ac, 3);
		while (wait(NULL) > 0)
			;
		return (1);
	}
	return (0);
}
