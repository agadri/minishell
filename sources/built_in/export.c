#include "../../includes/minishell.h"

char *ft_strcpy(char *src, char *dest)
{
	int	i;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

void	built_in_export(t_lexer *lexer, char *var)
{
	int	i;
	char	**tab;

	i = 0;
	while (lexer->command->tab[i])
		i++;
	lexer->command->tab_size = i + 1;//nouvelle taille de tab;
	tab = malloc(sizeof(char *) * lexer->command->tab_size + 2);//malloc tab avec sa nouvelle taille 
	if (!tab)//petite secu des familles
		return ;
	i = 0;
	// la je copie et malloc (realloc) dans tab;
	while (lexer->command->tab[i])
	{
		tab[i] = ft_strdup(lexer->command->tab[i]);
		i++;
	}
	tab[i] = ft_strdup(var);//lea je copie la nouvelle variable 
	tab[i + 1] = NULL;
	if (lexer->command->tab)//jsp si necessaire mais free l'ancien tab
	{
		lexer->command->tab = NULL;
		free(lexer->command->tab);
	}
	lexer->command->tab = malloc(sizeof(char *) * lexer->command->tab_size + 2);// je le remalloc
	if (!lexer->command->tab)
		return ;
	i = 0;
	while (tab[i])// et recopie dedans bam;
	{
		lexer->command->tab[i] = ft_strdup(tab[i]);
		i++;
	}
}