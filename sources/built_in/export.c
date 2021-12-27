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
/*
int	built_in_export(t_lexer *lexer, char *var)
{
	int	size;
	int	i;

	size = 0;
	i = 0;
	while (lexer->command->tab[size] != NULL)
		size++;
	lexer->command->tab[size + 1] = malloc(sizeof(char) * (ft_strlen(var) + 1));
	if (!lexer->command->tab[size + 1])
		return (0);
	while (var[i] != '\0')
	{	
		lexer->command->tab[size + 1] = ft_strdup(var);
		printf("%c", lexer->command->tab[size + 1][i]);
		i++;
	}
	printf("\n ||");
	return (1);
}
*/
/////
void	built_in_export(t_lexer *lexer, char *var)
{
	int	i;
	char	**tab;

	i = 0;
	while (lexer->command->tab[i])
	{
		//printf("lexer->command->tab : %s\n", lexer->command->tab[i]);
		i++;
	}
	//printf("sizeiiiii %d\n", i);
	lexer->command->tab_size = i + 1;
	tab = malloc(sizeof(char *) * lexer->command->tab_size + 2);
	//printf("--> sizeee : %d\n", lexer->command->tab_size);
	if (!tab)
		return ;
	
	i = 0;
	while (lexer->command->tab[i])
	{
		tab[i] = ft_strdup(lexer->command->tab[i]);
		//printf("tab : %s | lexer->command->tab : %s\n", tab[i], lexer->command->tab[i]);
		i++;
	}
	tab[i] = ft_strdup(var);
	//printf("tab : %s | var : %s\n", tab[i], var);
	tab[i + 1] = NULL;
	if (lexer->command->tab)
	{
		lexer->command->tab = NULL;
		free(lexer->command->tab);
	}
	lexer->command->tab = malloc(sizeof(char *) * lexer->command->tab_size + 2);
	//printf("--> sizeee : %d\n", lexer->command->tab_size);
	if (!lexer->command->tab)
		return ;
	i = 0;
	while (tab[i])
	{
		lexer->command->tab[i] = ft_strdup(tab[i]);
		//printf("tab : %s | lexer->command->tab : %s\n", tab[i], lexer->command->tab[i]);
		i++;
	}
}