#include <stdio.h>
#include <string.h>

int main()
{
	int	i;

	i = 1;
	while (i < 107)
	{
		printf("i = %3d	:	%s\n",i,strerror(i));
		i++;
	}
	return (0);
}
