/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:19:57 by tomsato           #+#    #+#             */
/*   Updated: 2025/03/21 13:48:38 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
Take an array and an index as arguments.
Convert the selected element into the format required by execve.
This can be easily achieved using split.
*/

char	**get_execve_argv(char **av, size_t index)
{
	const char** result = ft_split(av[index], ' ');
	return result;
}
