#ifndef PIPEX_H
# define PIPEX_H

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../libft/libft.h"

char	**get_execve_argv(char **av, size_t index);

#endif