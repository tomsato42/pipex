/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:14:56 by tomsato           #+#    #+#             */
/*   Updated: 2025/03/26 18:11:23 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

char	**get_execve_argv(char **av, size_t index);
void	exit_with_error(char *error);
char	*find_command_path(char *command, char **envp);
void	execute_command(char **av, int index, char **envp);
void	handle_here_doc(char *limitter);
int		recursive_piping(int current_index, int ac, char **av, char **envp);
char	**ft_split_with_quotes(const char *str);
/*iterative_piping funcs*/
void	safe_dup2(int oldfd, int newfd, const char *error_message);
void	setup_pipe(int pipe_fd[2]);
void	handle_outfile(char **av, int ac, char **envp, int prev_pipe_read);
pid_t	create_fork(void);
void	setup_child_io(int prev_pipe, int pipe_fd[2]);
int		process_middle_cmd(char **av, int ac, char **envp, int prev_pipe);
int		iterative_piping(int ac, char **av, char **envp);
void	setup_here_doc_io(int prev_pipe, int pipe_fd[2], int is_last);
void	setup_here_doc_out(char **av, int ac);
void	process_here_doc_child(char **av, char **envp, int ac, int i);
void	process_here_doc_cmds(char **av, char **envp, int ac, int i);
int		handle_here_doc_iterative(char **av, char **envp, int ac);

int		process_pipeline(int ac, char **av, char **envp);

#endif
