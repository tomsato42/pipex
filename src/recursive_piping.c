/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_piping.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:58:05 by tomsato           #+#    #+#             */
/*   Updated: 2025/03/21 19:28:57 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_with_error(char *error)
{
	perror(error);
	exit(EXIT_FAILURE);
}

int	recursive_piping(int current_index, int ac, char **av)
{
	int		pipefd[2];
	int		fd;
	pid_t	cpid;
	char	**execve_argv;
	ssize_t	bytes_read;
	char	buffer[1024];
	int		fd;

	char *const envp[] = {NULL};
	if (current_index == 1)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
			exit_with_error("open infile");
		if (dup2(fd, STDIN_FILENO) < 0)
			exit_with_error("dup2 infile");
		close(fd);
		return (0);
	}
	if (pipe(pipefd) == -1)
		exit_with_error("pipe");
	cpid = fork();
	if (cpid == -1)
		exit_with_error("pipe");
	if (cpid = 0)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) < 0)
			exit_with_error("dup2");
		close(pipefd[1]);
		
		// こっちは分裂する、最後はINPUT_FILEを入力として渡す。
	}
	else
	{
		close(pipefd[1]);
		waitpid(cpid, NULL, 0);
		if (dup2(pipefd[0], STDIN_FILENO) < 0)
			exit_with_error("dup2");
		if (current_index == ac - 1)
		{
			fd = open(av[current_index], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			while (1)
			{
				bytes_read = read(pipefd[0], buffer[1024], sizeof(buffer));
				if (bytes_read < 0)
					break ;
				write(fd, buffer, bytes_read);
			}
			if (bytes_read == -1)
			{
				close(fd);
				close(pipefd[0]);
				exit_with_error("read");
			}
		}
		else
		{
			execve_argv = ft_split(av[current_index], ' ');
			if (execve(execve_argv[0], (char *const *)execve_argv, envp) == -1)
				exit_with_error("execve");
			perror("execve");
			// execve_argvをfreeする関数作る
			exit(EXIT_FAILURE);
		}
	}
}

int	main(int ac, char **av)
{
	printf("ac :%d\n", ac);
	recursive_piping(ac - 1, ac, av);
	return (0);
}