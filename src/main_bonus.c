/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:54:39 by tomsato           #+#    #+#             */
/*   Updated: 2025/04/02 21:54:50 by tomsato          ###   ########.fr       */
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
