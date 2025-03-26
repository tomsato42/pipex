/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 02:31:34 by tomsato           #+#    #+#             */
/*   Updated: 2025/03/26 17:13:43 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	if (ac < 5)
	{
		write(STDERR_FILENO, "Error: Invalid number of arguments.\n", 37);
		return (1);
	}
	process_pipeline(ac, av, envp);
	return (0);
}
