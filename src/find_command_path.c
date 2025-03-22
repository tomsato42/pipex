/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 23:03:56 by tomsato           #+#    #+#             */
/*   Updated: 2025/03/23 00:16:09 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_full_path(char *path, char *command)
{
	char	*path_and_slush;

	path_and_slush = ft_strjoin(path, "/");
	if (!path_and_slush)
		exit_with_error("malloc");
	return (ft_strjoin(path_and_slush, command));
}

char	*find_command_path(char *command, char **envp)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	size_t	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i] != NULL)
	{
		full_path = get_full_path(paths[i], command);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
		{
			// don foget free paths
			return (full_path);
		}
		free(full_path);
		i++;
	}
	// don foget free paths
	return (NULL);
}

// int	main(int ac, char **av, char **envp)
// {
// 	printf("%s\n",find_command_path("ls", envp));
// 	return (0);
// }
