#include "../../includes/minishell.h"

// regroupe les commandes 

int	is_built_in(char *cmd)//je guete sur quelle commade je tombe 
{
	printf("11\n");
	char	*tab[] = {"echo", "cd", "pwd", "export", "unset", "env","exit", NULL};
	int	i;

	i = 0;
	printf("22\n");
	if (!cmd)
		return (2);
	printf("33\n");
	while (tab[i]) 
	{
		printf("44\n");
		if (!ft_strcmp(tab[i], cmd))//dans le cas ou cela ne correspond a aucun cas ...
			return (1);
		i++;
	}//ici sa merder
	return (0);
}

