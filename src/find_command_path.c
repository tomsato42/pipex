/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 23:03:56 by tomsato           #+#    #+#             */
/*   Updated: 2025/03/23 01:04:46 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_full_path(char *path, char *command)
{
	char	*path_and_slush;
	char	*result;

	path_and_slush = ft_strjoin(path, "/");
	if (!path_and_slush)
		exit_with_error("malloc");
	result = ft_strjoin(path_and_slush, command);
	free(path_and_slush);
	return (result);
}

static char	*serch_path(char *path_env, char *command)
{
	char	**paths;
	char	*full_path;
	size_t	i;

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
			ft_free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

char	*find_command_path(char *command, char **envp)
{
	char	*path_env;
	size_t	i;

	i = 0;
	path_env = NULL;
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
	return (serch_path(path_env, command));
}

// int	main(int ac, char **av, char **envp)
// {
// 	char *result;

// 	(void)ac;
// 	(void)av;
// 	result = find_command_path("ls", envp);
// 	printf("%s\n",result);
// 	free(result);
// 	system("leaks find_command_path");
// 	return (0);
// }
