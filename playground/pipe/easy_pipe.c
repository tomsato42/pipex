/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:58:22 by tomsato           #+#    #+#             */
/*   Updated: 2025/03/06 19:58:23 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

char	**get_execve_argv(const char *cmd, const char *option)
{
	char	**result;

	result = malloc(3 * sizeof(char *));
	if (!result)
		return (NULL);
	result[0] = strdup(cmd);
	result[1] = strdup(option);
	result[2] = NULL;
	return (result);
}

int	main(int ac, char **av)
{
	int		pipefd[2];
	pid_t	cpid_1;
	pid_t	cpid_2;
	char	**execve_argv;
	char	*cmd_1;
	char	*cmd_1_option;
	char	*cmd_2;
	char	*cmd_2_option;

	// const char	*cmd_1 = "/bin/ls";
	// const char	*cmd_1_option = "-l";
	// const char	*cmd_2 = "/bin/wc";
	// const char	*cmd_2_option = "-l";
	if (ac != 5) // pipexは通常5つの引数が必要
	{
		//エラーメッセージは今のところめちゃくちゃ
		fprintf(stderr, "Error: insufficient arguments\n");
		fprintf(stderr, "Usage: %s file1 cmd1 cmd2 file2\n", av[0]);
		fprintf(stderr, "Example: %s infile \"ls -l\" \"wc -l\" outfile\n",
			av[0]);
		exit(EXIT_FAILURE);
	}
	cmd_1 = av[1];
	cmd_1_option = av[2];
	cmd_2 = av[3];
	cmd_2_option = av[4];
	char *const envp[] = {NULL};
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	cpid_1 = fork();
	if (cpid_1 == 0)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		{
			perror("cmd1 dup2");
			exit(EXIT_FAILURE);
		}
		close(pipefd[0]);
		execve_argv = get_execve_argv(cmd_1, cmd_1_option);
		if (!execve_argv)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		if (execve(cmd_1, (char *const *)get_execve_argv(cmd_1, cmd_1_option),
				envp) == -1)
		{
			perror("execve cmd1");
			exit(EXIT_FAILURE);
		}
		perror("execve cmd1");
		free(execve_argv[0]);
		free(execve_argv[1]);
		free(execve_argv);
		exit(EXIT_FAILURE);
	}
	cpid_2 = fork();
	if (cpid_2 == 0)
	{
		close(pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) < 0)
		{
			perror("cmd2 dup2");
			close(pipefd[0]);
			exit(EXIT_FAILURE);
		}
		close(pipefd[1]);
		execve_argv = get_execve_argv(cmd_1, cmd_1_option);
		if (execve(cmd_2, (char *const *)get_execve_argv(cmd_2, cmd_2_option),
				envp) == -1)
		{
			perror("execve cmd2");
			exit(EXIT_FAILURE);
		}
		perror("execve cmd2");
		free(execve_argv[0]);
		free(execve_argv[1]);
		free(execve_argv);
		exit(EXIT_FAILURE);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(cpid_1, NULL, 0);
	waitpid(cpid_1, NULL, 1);
	return (0);
}
