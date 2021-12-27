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