#include "../../includes/minishell.h"

// regroupe les commandes 

int	is_built_in(char *cmd)//je guete sur quelle commade je tombe 
{
	char	*tab[] = {"echo", "cd", "pwd", "export", "unset", "env","exit"};
	int	i;

	i = 0;
	while (tab[i]) 
	{
		if (!ft_strcmp(tab[i], cmd))//dans le cas ou cela ne correspond a aucun cas ...
			return (1);
		i++;
	}
	return (0);
}

void	built_in(char *cmd, t_lexer *lexer)
{
	(void)lexer;
	//if (!strcmp(cmd, "echo"))
	//	built_in_echo();
	//if (!strcmp(cmd, "cd"))
	//	built_in_cd();
	//if (!strcmp(cmd, "pwd"))
	//	built_in_pwd();
	//if (!strcmp(cmd, "export"))
	//	built_in_export();
	//if (!strcmp(cmd, "unset"))
	//	built_in_unset();
	//if (!strcmp(cmd, "env"))
	//	built_in_env();
	if (!strcmp(cmd, "exit"))
		exit(0);
}
