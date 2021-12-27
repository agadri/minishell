#include "../../includes/minishell.h"



/*
int		built_in_echo(t_lexer *lexer)// ou args // ou str en fonction de se aue tu veux 
{
	int		i;
	int		option;

	i = 1;
	option = 0;
	//printf("suite %s\n", lexer->command->token[1].data);
	//printf("data len %d\n", lexer->command->token->data_len);
	char	*temp;
	temp = malloc(sizeof(char) * ft_strlen(lexer->command->token[1].data));
	if (!temp)
		return (0);
	temp = ft_strcpy(lexer->command->token[1].data, temp);
	if (nb_args(lexer->command->token[1].data) > 1)// nb d'arg
	{
		while (temp[i] && ft_strcmp(temp[i], "-n") == 0)//si arg[i] == "-n" donc pas de \n
		{
			option = 1;//met option en 1 pour indiquer qu'il y eu une option 
			i++;
		}
		while (temp[i])//si il y a un text a afficher
		{
			ft_putstr(temp[i]);//affiche le text
			if ((temp[i] != NULL) && temp[i + 1])//dans le cas ou args[i] n'est pas la fin et au'il n'y a rien apres(' ') affiche (' ')
				write(1, " ", 1);
			i++;
		}
	}
	if (option == 0)// si il y a deja eu une option
		write(1, "\n", 1);//met un \n apres 
	return (1);
}
*/