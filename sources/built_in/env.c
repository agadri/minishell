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
	if (lexer->state_of_init == 1)
		return (0);
	size = 0;
	i = 0;
	while (env[size] != NULL)// je prend la taille du tableau pour malloc 
		size++;
	lexer->command->tab_size = size;
	lexer->command->tab = malloc(sizeof(t_tab *) * (size + 1));
	if (!lexer->command->tab)
		return (0);
	lexer->command->tab[size] = NULL;
	while (env[i])
	{
		lexer->command->tab[i] = malloc(sizeof(t_tab));
		if (!lexer->command->tab[i])
			return (0);
		
		lexer->command->tab[i]->args = ft_argsdup(env[i]);// je copie tt en mallocant dans le tableau
		lexer->command->tab[i]->val = ft_valdup(env[i]);
		if (!ft_strcmp(lexer->command->tab[i]->args,"HOME"))
			lexer->command->home = ft_valdup(env[i]);
		if (!ft_strcmp(lexer->command->tab[i]->args,"OLDPWD"))
			lexer->command->oldpwd = ft_valdup(env[i]);
		i++;
	}
	return (1);//si tt est ok
}

void	built_in_env(t_lexer *lexer)//la j'affiche juste l'env
{
	int		i;

	i = 0;
	while (lexer->command->tab[i])
	{
		if (!ft_strcmp(lexer->command->tab[i]->args,"PWD"))//affiche pwd actuel
		{
			printf("env[%d] :%s=%s\n", i,lexer->command->tab[i]->args, built_in_pwd(lexer));
			i++;
		}
		else if (!ft_strcmp(lexer->command->tab[i]->args,"OLDPWD"))//l'ancien
		{
			printf("env[%d] :%s=%s\n", i, lexer->command->tab[i]->args,lexer->command->oldpwd);
			i++;//probleme passe un i a voir
		}
		else
			printf("env[%d] :%s=%s\n", i,lexer->command->tab[i]->args,lexer->command->tab[i]->val);
		i++;
	}
}

