#include "../../includes/minishell.h"

//unset supprime une variable et sa valeur dans env

int	built_in_unset(t_lexer *lexer, char *var)
{
	int	i;
	t_tab	**tab;

	i = 0;
	while (lexer->command->tab[i])
		i++;
	lexer->command->tab_size = i - 1;//nouvelle taille de tab;
	tab = malloc(sizeof(t_tab *) * lexer->command->tab_size + 1);//malloc tab avec sa nouvelle taille 
	if (!tab)//petite secu des familles
		return (0);
	i = 0;
	// la je copie et malloc (realloc) dans tab;
	while (lexer->command->tab[i])
	{
		
		if (ft_strcmp(lexer->command->tab[i]->args, var))// si dans le tableau il y a la variable on ne la copie pas 
		{
			tab[i] = malloc(sizeof(t_tab) * 1);
			if (!tab[i])
				return (0);
			tab[i]->args = lexer->command->tab[i]->args;
			tab[i]->val = lexer->command->tab[i]->val;
		}
		i++;
	}
	while (lexer->command->tab[i])//free l'ancien tab
	{
		lexer->command->tab[i] = NULL;//NULL et free sur l'ancien tab
		free(lexer->command->tab[i]);
		i++;
	}
	if (lexer->command->tab)//free l'ancien tab
	{
		lexer->command->tab = NULL;
		free(lexer->command->tab);
	}
	lexer->command->tab = malloc(sizeof(char *) * lexer->command->tab_size);// je le remalloc
	if (!lexer->command->tab)
		return (0);
	i = 0;
	while (tab[i])// et recopie dedans bam;
	{
		lexer->command->tab[i] = malloc(sizeof(t_tab) * 1);
		if (!lexer->command->tab[i])
			return (0);
		lexer->command->tab[i]->args = ft_strdup(tab[i]->args);
		lexer->command->tab[i]->val = ft_strdup(tab[i]->val);
		i++;
	}
	return (1);
}