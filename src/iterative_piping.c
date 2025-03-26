/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterative_piping.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:10:13 by tomsato           #+#    #+#             */
/*   Updated: 2025/03/26 18:09:47 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	process_middle_cmd(char **av, int ac, char **envp, int prev_pipe)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		i;

	i = 2;
	while (i < ac - 2)
	{
		if (pipe(pipe_fd) == -1)
			exit_with_error("pipe");
		pid = create_fork();
		if (pid == 0)
		{
			setup_child_io(prev_pipe, pipe_fd);
			execute_command(av, i, envp);
			exit(EXIT_SUCCESS);
		}
		close(pipe_fd[1]);
		close(prev_pipe);
		prev_pipe = pipe_fd[0];
		i++;
	}
	return (prev_pipe);
}

int	iterative_piping(int ac, char **av, char **envp)
{
	int		prev_pipe_read;
	pid_t	pid;

	prev_pipe_read = open(av[1], O_RDONLY);
	if (prev_pipe_read == -1)
		exit_with_error("open infile");
	prev_pipe_read = process_middle_cmd(av, ac, envp, prev_pipe_read);
	pid = create_fork();
	if (pid == 0)
		handle_outfile(av, ac, envp, prev_pipe_read);
	close(prev_pipe_read);
	while (wait(NULL) > 0)
		;
	return (0);
}

int	process_pipeline(int ac, char **av, char **envp)
{
	if (ac >= 6 && handle_here_doc_iterative(av, envp, ac))
		return (0);
	return (iterative_piping(ac, av, envp));
}
