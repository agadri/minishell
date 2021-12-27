#include "../../includes/minishell.h"

//unset supprime une variable et sa valeur dans env

int	ft_strcmpr(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
/*
int	built_in_unset(char **tab, char *var)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(tab[i] != NULL)
	{
		if (!ft_strcmp(tab[i], var))
		{
			while (tab[i][j])
			{
				tab[i][j] = '\0';//je remplace chaque char par '\0' pour supprimer
				j++;
			}
			return (0);
		}
		i++;
	}
	return (1);
}
*/
/////
int	built_in_unset(t_lexer *lexer, char *var)
{
	int	i;
	char	**tab;

	i = 0;
	while (lexer->command->tab[i])
		i++;
	lexer->command->tab_size = i - 1;//nouvelle taille de tab;
	tab = malloc(sizeof(char *) * lexer->command->tab_size);//malloc tab avec sa nouvelle taille 
	if (!tab)//petite secu des familles
		return (0);
	i = 0;
	// la je copie et malloc (realloc) dans tab;
	while (lexer->command->tab[i])
	{
		if (ft_strcmp(lexer->command->tab[i], var))// si dans le tableau il y a la variable on ne la copie pas 
			tab[i] = ft_strdup(lexer->command->tab[i]);
		i++;
	} 
	if (lexer->command->tab)//jsp si necessaire mais free l'ancien tab
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
		lexer->command->tab[i] = ft_strdup(tab[i]);
		i++;
	}
	return (1);
}