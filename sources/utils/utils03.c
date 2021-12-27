#include "../../includes/minishell.h"

void	remove_all_dollar_from_command(t_command *command)
{
	int i;
	
	i = 0;
	while (i < command->n_token)
	{
		if (command->token[i].type == ARG)
		{
			while (is_dollar(command->token[i].data))
				command->token[i].data = treat_dollar(command->token[i].data);
			while (is_dollar_2(command->token[i].data))
				command->token[i].data = treat_dollar_in_dquote(command->token[i].data);
		}
		i++;
	}
}

char	*remove_all_quote(char *str)
{
	int		i;
	int		count;
	char	*dest;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
			{
				i++;
				count++;
			}
			if (str[i] == '\'')
				i++;
		}
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"')
			{
				i++;
				count++;
			}
			if (str[i] == '\"')
				i++;
		}
		else
		{
			i++;
			count++;
		}
	}
	dest = (char *)malloc(sizeof(char) * (count + 1));
	if (!dest)
		return (NULL);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
			{
				dest[count] = str[i];
				i++;
				count++;
			}
			if (str[i] == '\'')
				i++;
		}
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"')
			{
				dest[count] = str[i];
				i++;
				count++;
			}
			if (str[i] == '\"')
				i++;
		}
		else
		{
			dest[count] = str[i];
			i++;
			count++;
		}
	}
	dest[count] = '\0';
	free(str);
	return (dest);
}

void	remove_all_quote_from_command(t_command *command)
{
	int i;

	i = 0;
	while (i < command->n_token)
	{
		command->token[i].data = remove_all_quote(command->token[i].data);
		i++;
	}
}

int is_dollar_sep(char c)
{
	if ( 37 == c || 58 == c || 61  == c || 63  == c
		|| 91  == c || 93  == c || 94  == c || 64 == c
		|| 123  == c || 125  == c || 126  == c
		|| (42 <= c && c <= 47) || c == '_')
		return (1);
	return (0);
}

void	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}
/*
int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	printf("555\n");
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
*/
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	printf("ls = %s cmd = %s\n", s2, s1);
	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i])
	{
		
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}