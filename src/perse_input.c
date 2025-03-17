#include "../libft/libft.h"

/*
input -> argc,argv

1-> ac - 1
2-> commands
3-> null or options
output -> char ***
*/

typedef struct s_command
{
	char	*command;
	char	*option;
} t_command;

t_command	*parce_input(int ac, char **av)
{
	size_t	i;
	char	*space_point;
	t_command	*return_value;

	return_value = (t_command *)malloc(sizeof(t_command) * (ac - 1));
	i = 1;
	while(i < ac)
	{
		while(ft_isspace(av[i]))
			av[i]++;
		space_point = ft_strchr(av[i], ' ');
		return_value->command = ft_substr(av[i], 0, space_point - av[i]);
		av[i] += space_point - av[i];
		while(ft_isspace(av[i]))
			av[i]++;
		
	}

	return ;
}
