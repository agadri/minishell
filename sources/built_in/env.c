#include "../../includes/minishell.h"

//env affiche l'environnement donc le copie le tableau 
// pour pouvoir y avoir acces plus tars et je l'affiche ..
//SHLVL
int	take_and_cpy_env(char **env, t_lexer *lexer)
{
	int	size;
	int	i;
	if (!env)
		return (0);
	if (lexer->command->state_of_init == 1)
		return (0);
	size = 0;
	i = 0;
	while (env[size] != NULL)// je prend la taille du tableau pour malloc 
		size++;
	lexer->command->tab_size = size;
	printf("size env %d\n", size);
	lexer->command->tab = malloc(sizeof(char *) * (size + 1));
	if (!lexer->command->tab)
		return (0);
	while (env[i])
	{
		lexer->command->tab[i] = ft_strdup(env[i]);// je copie tt en mallocant dans le tableau
		//printf("env[%d] :%s\n", i,env[i]);
		//printf("lexer->command->tab[%d] : %s\n", i, lexer->command->tab[i]);
		i++;
	}
	return (1);//si tt est ok
}

void	built_in_env(t_lexer *lexer)//la j'affiche juste l'env
{
	int	i;

	i = 0;
	while (lexer->command->tab[i] != NULL)
	{
		printf("%s\n", lexer->command->tab[i]);
		i++;
	}
}