/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:14:56 by tomsato           #+#    #+#             */
/*   Updated: 2025/03/26 14:41:29 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>

char	**get_execve_argv(char **av, size_t index);
void	exit_with_error(char *error);
char	*find_command_path(char *command, char **envp);
void	execute_command(char **av, int index, char **envp);
void	handle_here_doc(char *limitter);
int		recursive_piping(int current_index, int ac, char **av, char **envp);
char	**ft_split_with_quotes(const char *str);

#endif
