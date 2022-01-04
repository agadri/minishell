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
	t_tab 	**tab;

	i = 0;
	//taille 
	while (lexer->command->tab[i])
		i++;
	lexer->command->tab_size = i + 1;//nouvelle taille de tab;
	tab = malloc(sizeof(t_tab *) * lexer->command->tab_size + 2);//malloc tab avec sa nouvelle taille 
	if (!tab)//petite secu des familles
		return ;
	i = 0;
	// la je copie et malloc (realloc) dans tab;
	while (lexer->command->tab[i])
	{
		tab[i] = malloc(sizeof(t_tab) * 1);
		if (!tab[i])
			return ;
		tab[i]->args = ft_strdup(lexer->command->tab[i]->args);
		tab[i]->val = ft_strdup(lexer->command->tab[i]->val);
		//printf("env[%d] :%s %s\n", i,lexer->command->tab[i]->args,lexer->command->tab[i]->val);
		i++;
	}
	tab[i] = malloc(sizeof(t_tab) * 1);//args et val
	tab[i + 1] = malloc(sizeof(t_tab) * 1);//'\0'
	if (!tab[i] || !tab[i + 1])
		return ;
	tab[i]->args = ft_argsdup(var);//la je copie la nouvelle variable 
	tab[i]->val = ft_valdup(var);//pareil
	tab[i + 1]->args = NULL;
	tab[i + 1]->val = NULL;
	i = 0;
	while (lexer->command->tab[i])//free l'ancien tab
	{
		lexer->command->tab[i] = NULL;//NULL et free sur l'ancien tab
		free(lexer->command->tab[i]);
		i++;
	}
	lexer->command->tab = NULL;
	free(lexer->command->tab);
	lexer->command->tab = malloc(sizeof(t_tab *) * lexer->command->tab_size + 2);// je le remalloc
	if (!lexer->command->tab)
		return ;
	i = 0;
	while (tab[i]->args)// et recopie dedans bam;
	{
		lexer->command->tab[i] = malloc(sizeof(t_tab) * 1);
		if (!lexer->command->tab[i])
			return ;
		lexer->command->tab[i]->args = ft_strdup(tab[i]->args);
		lexer->command->tab[i]->val = ft_strdup(tab[i]->val);
		i++;
	}
}